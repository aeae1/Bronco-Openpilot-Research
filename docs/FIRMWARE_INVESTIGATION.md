# Bronco openpilot: independent firmware investigation

**Follow-up available:** [application consumers, startup selection, and remaining gates](POST_VALIDATION_FINDINGS.md). That update traces LMC2 beyond the stopping point in this initial report and verifies a narrow correction to the analysis tool. The initial evidence below is retained as the baseline; its store-width limitation is addressed in the follow-up excerpts.

Prepared with ChatGPT/Codex; see [provenance and credits](../THIRD_PARTY.md).

**Research date:** September 14, 2026  
**Target:** 2024 full-size Ford Bronco, with factory adaptive cruise control. This is not the Bronco Sport.  
**Constraint:** preserve factory steering protections and independent openpilot/Panda safety checks.

## Result

**The public Bronco steering-controller firmware contains a traceable receive and validation path for the same lane-centering message that openpilot uses on supported Ford vehicles.** I followed it beyond the CAN-ID table, corrected a consequential table interpretation, located its receive and timeout callbacks, and independently compared its checksum routine with openpilot. All 10,640 offline comparison cases matched.

That materially strengthens the case for pursuing the factory interface. It does **not** establish that the target vehicle's 2024 rack runs this firmware, that the message reaches it through its gateway, or that its steering application will permit sustained lane centering. I have not produced a working Bronco port or a safety validation.

All work was on public files and local analysis tools. No vehicle connection, diagnostic write, firmware alteration, steering command, or message to a community member was made.

## What was actually inspected

The primary material is the three Bronco VBF files published in [ghostdev137/ford-pscm-re at revision f545afe](https://github.com/ghostdev137/ford-pscm-re/tree/f545afe509aa936a32ad026d411add394f8464ae/firmware/Bronco_6G). These are a public sample, not a readout of the target vehicle.

| File | VBF bytes | Main extracted block | Independently checked |
|---|---:|---:|---|
| NB3C-14D003-AB.VBF | 1,571,613 | 1,569,792 bytes | Download hash, two block CRCs, extracted program matches the separately published binary |
| NB3C-14D004-AD.VBF | 64,284 | 62,464 bytes | Download hash and two block CRCs |
| NB3C-14D007-AAB.VBF | 195,361 | 193,536 bytes | Download hash and two block CRCs |

All six block CRC16 checks passed. This establishes consistency of the retrieved files and their blocks; it does not authenticate them as Ford-approved releases or establish vehicle compatibility. I did not verify the header checksum algorithm or cryptographic signatures. The header's “Unsigned” description is not evidence that a controller accepts unsigned firmware.

I also downloaded pinned snapshots of [upstream opendbc](https://github.com/commaai/opendbc/tree/057aee25b5eee7530f0b95b5b508c8c3247b0cd7) and the [mims002 experimental fork](https://github.com/mims002/opendbc/tree/690bcf4a60d22a445e007a7766a0914d9739b8ef). Exact URLs and SHA-256 hashes are in the accompanying manifests.

## Finding 1: the published receive-table alignment is wrong

The public README groups words as `handler, CAN ID, sentinel` and consequently associates `0x0003081E` with LMC2. The consuming code instead reads a 12-byte record with this layout:

| Byte offset | Interpretation established from the receiving code |
|---:|---|
| +0…3 | CAN ID |
| +4…7 | Mask and search-control flags |
| +8 | Upper-layer PDU ID |
| +9 | Length field; low seven bits participate in the minimum-length check |
| +10 | Receive-callback selector |
| +11 | Frame-type filter |

The full arrays begin at CPU addresses **0x411F8** and **0x414E0** and span **62 records each**. They are referenced by configuration structures at 0x40F88 and 0x40F9C. Their existence does not, by itself, prove that both configurations are active simultaneously or represent two physical buses.

LMC2 is record 39 in both arrays. Its bytes are:

```text
d6 03 00 00  ff 07 00 40  17 08 03 00
```

Thus the relevant upper-layer PDU ID is **0x17 (23)** and its packed metadata is **0x00030817**. The preceding record is CAN ID **0x3D7**, with PDU ID **0x1E (30)**. Following the README's proposed PDU 30 would investigate a different message. The upstream [Ford DBC](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/dbc/ford_lincoln_base_pt.dbc) names 0x3D7 `Steer_Assist_Data`; the LMC2 rolling counter is a field inside 0x3D6.

**Evidence:** CAN lookup at CPU 0x84DCC reads the ID at record +0 and flags at +4. Dispatch at 0x84D46 reads +8, +9, and +10 for the upper-layer call. This correction follows the instructions that consume the table, not just a preferred way of grouping bytes.

The corrected arrays differ at five record positions, 16–20. Both contain identical LMC2, LKA, and AdvTrJamAsst entries. Neither has an explicit 0x3D3 LMC1 entry; that is not a claim about every possible masked or diagnostic receive path.

## Finding 2: a concrete LMC2 receive chain

The traced path is:

LMC2 (CAN ID `0x3D6`) maps to CAN-interface PDU 23, then route 31 and communications PDU 26, followed by arrival tracking and application validation. The table below records the evidence for each stage.

Function names such as CAN interface, PDU routing, and communications layer describe their observed behavior and AUTOSAR-like structure; the binary does not provide these source symbols.

| Step | CPU address / value | What the code establishes |
|---|---|---|
| Receive-table entry | 0x413CC or 0x416B4 | ID 0x3D6, minimum length 8, PDU 23, callback selector 3 |
| CAN lookup and dispatch | 0x84DCC → 0x84D46 | Message lookup plus initialization, controller/PDU-mode, length, and callback checks |
| Selected callback | 0x599C6 → 0xA41F0 | Forwards the PDU to the next routing layer |
| Routing tables | 0xA44AA → 0xA4430 | PDU 23 maps through route 31 and destination index 53 |
| Communications receiver | 0x8FA06, destination PDU 26 | Checks initialization, PDU enable state, and input validity; invokes the configured callout |
| PDU 26 configuration | 0x45030 | Enables callout 22 and an eight-byte deferred copy at buffer offset 0xCE |
| LMC2 receive callout | 0x6AA00 | Clears status byte 0xFEEDE85F, increments arrival byte 0xFEEDE874, returns success |
| Complementary callback | 0x6AA16 | Sets status byte 0xFEEDE85F to 1 |
| Application-side consumer | 0x74B76 | Branches on that status into a stale-data handling path or a received-data validation path |

The complementary callback's connection to a communication-timeout condition is a strong interpretation of the paired callbacks and application behavior. I have not reconstructed the complete communications scheduler and its physical timing.

The receive callout itself does not inspect the payload checksum; that check appears later. A packet arriving successfully is therefore a different milestone from the application accepting its data, and both precede any proof of steering actuation.

## Finding 3: the checksum matches openpilot

The application path at **0x74A1E** calls a straight-line checksum routine at **0x74904**, compares its result with the received checksum, and passes a mismatch indication into **0x74950**. It also compares arrival state and the message counter with prior values.

For in-range LMC2 fields, the checksum arithmetic is the low-byte complement of the sum of:

- The three-bit request mode and four-bit rolling counter.
- The low and high portions of the four numeric path fields, with their respective 11-, 11-, 10-, and 11-bit widths.

This agrees with upstream [calculate_lat_ctl2_checksum](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/fordcan.py).

To check the arithmetic independently, I wrote a small interpreter for the routine's exported integer/load/store instructions. I compared its output against the actual checksum function extracted from the pinned upstream Python source. The test used **640 boundary combinations plus 10,000 deterministic random cases: zero mismatches**.

This is a narrow, useful result. It is not a whole-controller emulator, CAN-bus replay, validation of physical timing, or a test that the wheel moves. It also does not establish the acceptability of every command mode. The protocol check found here is an ordinary checksum, not a secret-key authentication calculation; other gating or security mechanisms elsewhere have not been ruled out.

## Finding 4: freshness and error handling are present

The application functions at **0x747B4, 0x74A1E, and 0x74950** include timer-dependent behavior for missing/stale input, checksum mismatch, counter-related state, and a data-validity output. These are useful starting points for understanding why an arriving command might still be rejected or declared unusable.

The decoded fields also pass through 10- and 11-bit range handling. **Those ranges are signal-encoding bounds, not demonstrated steering-torque or lateral-acceleration safety limits.** I have not located and validated the complete motor-authority and driver-override chain.

This evidence supports investigating the stock protocol with its supervision intact. It does not support removing timeouts, forcing validity flags, increasing EPS limits, or claiming that a watchdog found here explains the vehicle's reported connection failure.

## Finding 5: the small file contains relevant calibration data

The public README tentatively labels NB3C-14D004-AD as “SBL?” The traced application uses parameters in this file through a ROM-default directory:

```text
Default directory 0x4BE4C
  pointer field at +0x6C = 0x4BEB8
  points to parameter structure 0x1C0168
```

Six fields referenced by the receive-validation and stale-data paths occupy CPU addresses **0x1C0350–0x1C035A**. Their raw 16-bit values in this default structure are **0, 950, 5000, 0, 950, 0**. The consuming code scales these values in timer comparisons.

The active configuration pointer can also select a RAM-built directory. Consequently these are **ROM-default values, not verified runtime values for the target vehicle**. I have not established the timer's physical units or proposed changing any of these fields. The justified conclusion is that at least part of the small file contains application calibration used by this path; its entire role need not be reduced to one label.

The six repeating arrays in the larger calibration file, previously proposed as authority envelopes, are present at the published offsets. Their steering-limit interpretation remains unproven. I did not mistake those arrays for validated torque limits.

## What this means for the target Bronco

The full-size Bronco is not listed as supported in the inspected [upstream Ford vehicle definitions](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/values.py). Bronco Sport support does not establish support for this vehicle.

There is a credible factory-interface research direction. The public sample has more than an isolated message ID: it has routing, arrival tracking, application consumption, and a familiar checksum. I did not find a reason in this traced portion that would require defeating a secure boot process or removing EPS protection to communicate using the expected command format.

However, **supported operation remains unproven**, for four separate reasons:

1. **Firmware identity:** the target vehicle's PSCM strategy and calibration IDs have not been matched to the public sample.
2. **Delivery:** a command seen at the camera connection need not reach the rack across the gateway and the different CAN segments.
3. **Application permission:** configuration, vehicle-state inputs, arbitration with other steering functions, and the complete acceptance conditions remain incompletely traced.
4. **System safety:** a working port still needs independent command bounds, proper disengagement and driver override, fault handling, correct vehicle geometry, and preservation of the intended ACC behavior.

The [first-hand Bronco development discussion](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-29) reported the legacy-CAN camera/CAN-FD rack mismatch and, in June 2026, a gateway-delivery problem plus termination trouble during direct-rack harness experiments. These are development reports, not measurements from the target Bronco. The [following discussion page](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-30) did not supply a verified production solution in the material reviewed.

The best hypothesis to pursue is therefore **correctly delivered, stock-format LMC2 with the required legitimate vehicle states and all supervision retained**. I cannot claim this idea is new; the deeper receive-chain mapping and corrected PDU association are independent results of this investigation. Private Discord discussion may already contain further work. I had no access to those private channels.

## Why the experimental fork is not a ready answer

The inspected [mims002 controller](https://github.com/mims002/opendbc/blob/690bcf4a60d22a445e007a7766a0914d9739b8ef/opendbc/car/ford/carcontroller.py) still uses the legacy LKA command for the full-size Bronco and contains logic intended to manage its availability/timeouts. That does not demonstrate the native LMC2 route above. Its time calculations use seconds while subtracting a literal 500 in one timeout comparison, a units concern that warrants correction or explanation.

More consequentially, its [LKA safety branch](https://github.com/mims002/opendbc/blob/690bcf4a60d22a445e007a7766a0914d9739b8ef/opendbc/safety/modes/ford.h) allows active LKA action when a special flag is set without applying a controls-allowed gate or independent LKA angle/rate bounds in that branch. Its [test source](https://github.com/mims002/opendbc/blob/690bcf4a60d22a445e007a7766a0914d9739b8ef/opendbc/safety/tests/test_ford.py) explicitly expects the flagged active command to pass after a controls-disabled check. This is a source audit; I did not run the complete fork safety suite. It is not a claim that every other Panda check is disabled.

The fork's [interface configuration](https://github.com/mims002/opendbc/blob/690bcf4a60d22a445e007a7766a0914d9739b8ef/opendbc/car/ford/interface.py) also enables openpilot longitudinal control for this Bronco profile. It should not be treated as a demonstrated lateral-only setup retaining the intended factory ACC behavior. These issues matter under the project's explicit safety constraint. Upstream describes the intended independent safety architecture in [its safety documentation](https://docs.comma.ai/concepts/safety/).

The [2024 demonstration video](https://www.youtube.com/watch?v=PpQoKbeA-WM) is useful historical context, but I did not watch its playback in this investigation or treat its existence as validation of continuous, safe support.

## Method and confidence limits

- **Address mapping:** VBF programming addresses begin at 0x10040000; executable pointers and startup code use a CPU view beginning at 0x40000. Startup establishes `tp = 0x48A00` and `gp = 0xFEBFFE7C`. The explicit TP load is at CPU 0x40086. These values replaced initial, incorrect analysis assumptions.
- **Decoder selection:** analysis compared pypcode, the repository's patched language, and official Ghidra 12.1.3. The final excerpts use `V850:LE:32:v850e3v5`. The patched language includes broad placeholder instruction definitions, and earlier decoders misread some loads or indirect calls. A plausible-looking decompilation is not sufficient evidence.
- **Decompiler limitations:** the installed common V850 language definition models one `st.w disp23` operation with a 16-bit store. Large application-function argument recovery also needs manual refinement. Exported C is navigational material, not a verified recompilable source reconstruction. Critical receive-record accesses were checked against assembly; the checksum test uses a separate interpreter for basic instructions.
- **Coverage:** this is targeted static analysis, not an exhaustive firmware audit. No claim of full instruction coverage, freedom from hidden gates, verified EPS limits, or vehicle-level safety is made.
- **Novelty:** “found here” means independently established during this investigation. It does not establish that nobody else has found it privately.

## Next evidence that would move the result forward

The most useful next input is a **read-only FORScan module-information export** showing PSCM, IPMA, and GWM hardware/software/calibration identifiers, plus the OBD adapter model. That would determine whether this exact analysis applies to your installed modules. Existing passive CAN captures or development logs could then distinguish gateway delivery from application rejection. Relevant Discord posts or attachments can be incorporated if supplied.

On the offline side, the next focused work is to follow the decoded LMC2 signals from the application interface into steering arbitration and its calibrated limits, resolve the active calibration-directory selection, and map legitimate enable conditions. The addresses above make that a concrete continuation rather than another broad search for the CAN ID.

## Reproduction

This repository contains original analysis scripts, pinned download manifests, structured findings, selected disassembly/decompilation excerpts, and the checksum comparison result. It excludes vehicle-control code, modified firmware, raw firmware payloads, and the large tool installations.

From the repository root, with Python 3.10 or newer and network access:

```bash
python3 fetch_firmware.py
python3 fetch_port_sources.py
python3 analyze_firmware.py
python3 check_checksum.py
```

The first script verifies pinned firmware hashes and never writes to a device. The structural script verifies all VBF block CRCs, reconstructs the receive tables and routing, and reads the default parameter fields. The checksum comparison uses the included instruction excerpt and the independently retrieved upstream checksum function. Ghidra scripts are included for regenerating the excerpts; setup and limitations are documented in the [reproduction guide](REPRODUCING.md).
