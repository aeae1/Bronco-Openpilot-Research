# Following LMC2 into the steering application

Research update: September 14, 2026. Applies to the pinned public NB3C firmware sample, not yet to the owner's installed modules.

**The strongest new result: the sample has application code that consumes LMC2 path data, and its startup defaults select that input branch.** This is more evidence than a receive-table entry or a matching checksum. It is still not proof that the steering state machine will authorize sustained assistance, that the gateway delivers the message, or that a vehicle port is safe.

The code and original firmware bytes were analyzed locally. The only correction made was to a dedicated Ghidra analysis installation. No vehicle was connected and no firmware was changed.

## What changed since the first investigation

| Earlier stopping point | New evidence | What remains open |
|---|---|---|
| LMC2 reaches checksum, freshness, and validity handling | Getters and callers connect its outputs to application input preparation, path scaling, and status checks | Full arbitration, driver override, final actuator authority, and fault behavior |
| Application input selection was unknown | A source-selection branch selects LMC2 with the sample's initialized bytes; targeted virtual execution confirms it | Whether later initialization/configuration changes those bytes in the owner's firmware |
| Decompiled configuration pointers appeared truncated | A verified four-byte-store correction restores the directory pointers | Other imperfect instruction semantics and function prototypes |
| Only the ROM receive-parameter directory was known | Two RAM directory banks, ROM fallback, and a separate RAM override for the receive-parameter slot are mapped | The directory and parameter values active on a real controller |

## 1. The message's values have application consumers

The first investigation stopped at `0x74B76`, which publishes decoded LMC2 fields and their validity state. Small getter functions retrieve those outputs. The following addresses are CPU addresses in this particular firmware revision.

| Field | Published RAM | Getter | Application use |
|---|---|---|---|
| Request mode | `0xFEBEECFC` | `0xBD56E` | Read by `0xED420` and by the LMC2 branch of `0xF3E34` |
| Curvature-rate raw field | `0xFEBEEBA2` | `0xBD516` | Scaled by approximately `0.000001`, then offset by `−0.001024` |
| Curvature raw field | `0xFEBEEBA4` | `0xBD526` | Scaled by approximately `0.00002`, then offset by `−0.02` |
| Path offset raw field | `0xFEBEEBA6` | `0xBD52E` | Scaled by approximately `0.01`, then offset by `−5.12` |
| Path heading raw field | `0xFEBEEBA8` | `0xBD536` | Scaled by approximately `0.0005`, then offset by `−0.5` |
| Validity state | `0xFEBEECF9` | Part of `0xBD05C` | Becomes bit 9 (`0x200`) of a broader status summary |

The four conversions agree with the corresponding fields of the pinned upstream [Ford LMC2 DBC definition](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/dbc/ford_lincoln_base_pt.dbc). They identify the input quantities; they do **not** establish steering torque limits, safe command envelopes, or the final amount of actuator authority. The application also bounds some intermediate values, but a complete numerical safety analysis has not been performed.

`0xED3E6` calls input preparation `0xED420`, then a larger stateful consumer `0xED884`, then output handling `0xED662`. The larger consumer reads the request mode and status results and contains branches, state memory, and rate-limiting calculations. Its complete meaning has not been recovered. This is a concrete next trace, not evidence that all its conditions pass.

In another application sequence, `0xF39EC` calls `0xF3E34`, then `0xF3D2E`, which schedules several additional routines. Those include `0x1187E2`, `0x119358`, `0x11AA5C`, and `0x11B0C0`. Their complete downstream behavior remains work for a subsequent analysis.

Evidence: [selected disassembly and provisional C](../results/followup/ghidra/), particularly `ed420`, `ed884`, `f3e34`, and `bd05c`. The C output is navigational: some float expressions and recovered function arguments are visibly imperfect. Critical pointer, selection, and status claims here were checked against instruction bytes and assembly.

## 2. The startup defaults select the LMC2 input branch

In `0xF3E34`, the input-source decision has the following observed condition. These labels describe the values' role in the comparison; they are not recovered Ford symbol names.

```text
Select the LMC2 branch if:
    selection_flag is nonzero
    OR selector_input equals expected_selector_code
```

The selected branch calls LMC2 getters `0xBD516` and `0xBD56E`. The alternate branch calls `0xBD51E` and `0xBD576`. Its different numeric scale resembles the older LMC definition, but its complete receive route was not reconstructed; it is called the **alternate source** here.

The values used in the comparison were traced through actual startup initialization:

1. Startup at `0x40098` calls `0xB8672`.
2. That initializer processes 271 records from `0x11BF30` to `0x11CBE4`, advancing 12 bytes each time. It passes destination at `+0`, source at `+4`, and a 16-bit byte count at `+8` to copying routine `0xDE040`.
3. Two of those copies initialize the selector input and the application's configuration block.

| Role | RAM address | Initializer record | Source byte | Initial value |
|---|---|---|---|---:|
| Selection flag | `0xFEF23886` | `0x11CBB4` | `0x1D62FE` | 0 |
| Expected selector code | `0xFEF23887` | `0x11CBB4` | `0x1D62FF` | 1 |
| Selector input returned by `0xBD486` | `0xFEBF6B0E` | `0x11C068` | `0x57D0E` | 1 |

Therefore the comparison succeeds using these initialized values: `0 != 0 OR 1 == 1` is true. **The sample does not require changing these startup bytes to select this particular LMC2 input branch.** This statement is deliberately limited to source selection. It does not mean the controller is ready to apply steering assistance.

Verification went beyond reading the decompiler. In Ghidra virtual memory, the actual copy routine reproduced all bytes of three relevant initialization records, with neighboring sentinel bytes intact. Their lengths were 55, 3,608, and 3,036 bytes. A short execution from the selector getter call to the conditional branch selected LMC2 using those copied defaults. Three contrasting virtual-input cases followed the expected branches as well. Those contrasting cases are analysis fixtures, not proposed settings for a vehicle.

Evidence: [selection check results](../results/followup/selection_check.tsv), [startup excerpt](../results/followup/startup.tsv), [reproduction script](../ghidra_scripts/BroncoSelectionCheck.java), and [static initialization findings](../results/followup/static_findings.json). This is not a full boot simulation. Later writes, runtime configuration, or a different installed firmware can change the result.

## 3. Valid LMC2 data is one prerequisite among several

Function `0xBD05C` assembles status bytes into a bitmask. A nonzero LMC2 validity byte sets bit 9. Application code then compares that summary with configured masks; it does not simply ask whether any LMC2 packet arrived.

Two initialized masks that include the LMC2 bit are:

| Consumer's mask address | Initialization source | Mask | Meaning established |
|---|---|---|---|
| `0xFEF23870` | `0x1D62E8` | `0x51780200` | Used in `0xF3E34`; all bits in this mask must be present for this individual comparison |
| `0xFEF2461C` | `0x1D7094` | `0x40080200` | Used in `0xED420`; all bits in this mask must be present for this individual comparison |

Both contain other bits in addition to `0x200`. The second comparison also feeds a combination with a different status test before the larger consumer reads it. Mapping every other bit to its original vehicle signal is unfinished.

This is a useful explanation of why “the packet checks out” does not automatically mean “the car will steer.” It is **not** evidence that any of these particular checks caused the reported gateway or connection failures.

## 4. A verified analysis-tool correction makes the configuration trace usable

Stock Ghidra 12.1.3's shared V850 definition decodes one `ST.W reg3, disp23[reg1]` instruction as a two-byte store in PCode. The [Renesas-authored RH850G3M software manual, revision 1.40, page 314](https://docs.alexrp.com/v850/rh850g3m.pdf) specifies a word store. Here that is four bytes. The manual is hosted on a third-party mirror; use of its instruction definition does not identify the Bronco's exact processor model.

The source definition was changed only in a dedicated local Ghidra installation, from a two-byte store to a four-byte store, and its language was rebuilt. The script checks the exact original source hash and retains backups. It does not modify any firmware file. See [the correction script](../fix_ghidra_stw.py) and [source/compiled-language hashes](../results/followup/tool_correction.json).

Two real firmware instructions, `0xD0910` and `0xD0CAC`, were executed individually against virtual memory with six source-register values each. Every stock case wrote only the low two bytes. Every corrected case wrote all four expected bytes and preserved the neighboring bytes: [12 stock failures](../results/followup/stw_stock.tsv), [12 corrected passes](../results/followup/stw_corrected.tsv). These are instruction-model tests, not tests of a vehicle safety system.

With that correction, the directory trace shows:

- The active directory pointer is stored at `0xFEBEE5D0`.
- Two RAM directory banks start at `0xFEBF62C4` and `0xFEBF6388`, 196 bytes apart: 48 pointer entries followed by an integrity word.
- `0xD08EC` selects the other bank, publishes its full pointer, and copies its directory into the previous bank. `0xD0B34` includes integrity handling and a fallback to the full ROM pointer `0x0004BE4C`.
- The 18-record variant table at `0x4C690` selects entries for modes 0–5 and changes destination slots 2, 31, and 42. It does not itself change slot 27, which holds the receive-validation parameters.
- A **different, conditionally used** table at `0x4C720` does include slot 27. Its entry can point that slot at RAM `0xFEED8004`. The actual runtime selection and contents there remain unknown.

Consequently, the six previously reported ROM timing values remain defaults, not proven values for a running vehicle. This directory work does not provide a reason to change calibrations or defeat their integrity checks.

## 5. Timing is clearer, but physical timeout units remain unresolved

The timestamp routine at `0xB773C` reads two consecutive words at `0xFFDD8040` and `0xFFDD8044`. Its instruction bytes identify an unsigned 64-bit-to-double conversion and double-precision division by **8000.0**, followed by conversion back to an integer and storage of the low 32 bits. `0xB77AA` subtracts a saved timestamp from the current value.

The conversion and division mnemonics printed by this Ghidra language are misleading (`cvtf.uls` and `divf.s` with paired registers). The actual encodings match **CVTF.ULD** and **DIVF.D** in the Renesas manual, pages 386 and 392. This analysis used those architectural meanings; it does not claim that every floating-point PCode operation is correct. In particular, unsigned conversion deserves care when comparing emulator behavior at very large values.

The underlying counter's frequency has not been established. Dividing by 8000 does not, by itself, prove that the resulting unit is a millisecond or that the original problem was a missing keep-alive. The full physical timing claim remains open.

## What this means for previous failures and future work

The [firsthand Bronco development discussion](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-29) reported a legacy-CAN camera/CAN-FD rack difference, gateway-delivery problems, and network termination trouble during direct-rack harness work. This investigation has not solved any of those physical delivery issues. It has now found a stronger reason to examine a correctly delivered native LMC2 request: the public sample has both application consumers and startup defaults that select its input branch.

That is separate from the earlier experimental fork's use of the older lane-assistance command and its changes to independent safety checks, discussed in the [initial source audit](FIRMWARE_INVESTIGATION.md#why-the-experimental-fork-is-not-a-ready-answer). No such changes were needed to establish the findings here.

As of this check, the public firmware repository's latest commit remains the [May 7, 2026 sample already analyzed](https://github.com/ghostdev137/ford-pscm-re/commit/f545afe509aa936a32ad026d411add394f8464ae). The latest change to upstream Ford vehicle definitions returned by GitHub was [August 9, 2026](https://github.com/commaai/opendbc/blob/d8f6d5cf9600f5c1861a09563568018cc4eb8025/opendbc/car/ford/values.py); those definitions list the Bronco Sport, not the full-size Bronco. Reviewed [follow-up forum discussion](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-30) did not establish a verified production solution. Private Discord discussion was not accessed, so this is not a claim to know every developer's current progress or to have universal priority on these findings.

The next offline work is to map the remaining status bits, trace the larger stateful consumers into final arbitration and override handling, and check further instruction semantics where those claims depend on them. Matching the owner's PSCM/IPMA/GWM identities is the next way to establish whether these exact findings apply to the vehicle; the [owner guide](OWNER_COLLECTION_GUIDE.md) explains what to collect. That information is helpful for relevance, **not a prerequisite for continuing offline analysis**.

There is now a better-supported reason for hope. There is still no installation, working port, or basis for changing factory steering protections.
