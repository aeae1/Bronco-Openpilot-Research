# What to send from your Bronco, FORScan, and OBD adapter

Prepared September 14, 2026, for the 2024 full-size Bronco investigation.

**You do not need to collect anything before the offline research can continue.** The public steering firmware is already available and analyzed. Your information helps determine how that research applies to the computers actually installed in your Bronco. A matched gateway executable remains missing; see [the firmware acquisition status](FIRMWARE_ACQUISITION.md).

The first collection is identification only. No firmware dump, programming, vehicle disassembly, or driving experiment is needed.

**September 15 update:** the owner supplied a Ford As-Built file, and all three target module records were extracted. [Results](ASBUILT_FINDINGS.md). No additional As-Built download is needed. **Connected-session identification is now also received**, including adapter/software details and module grouping. [FORScan results](FORSCAN_FINDINGS.md). No repeat scan is needed for this step; the instructions below remain a reusable guide. Matching executable firmware is still missing; requests use these [exact identifiers](FIRMWARE_FILE_REQUEST.md).

## The smallest useful packet

Send these in our chat. Photos or screenshots are enough; you do not need to interpret the numbers.

| Item | What to send | Why it helps |
|---|---|---|
| Your adapter | A clear photo of its label and any HS/MS switch; manufacturer/model; USB, Bluetooth, or Wi-Fi. An existing product link helps if the label is vague. | “ELM327” alone does not establish the adapter's capabilities. |
| Your software | FORScan version and device/operating system. For Lite, include its kernel version if displayed. | Lets us tailor the instructions to your actual screen and capabilities. |
| Steering computer | The complete **PSCM** identification section. | The most important comparison with the public steering firmware. |
| Camera computer | The complete **IPMA** identification section. | Identifies the factory camera software involved in lane assistance. |
| Network gateway | The complete **GWM** identification section, if exposed. | Identifies the computer connecting the vehicle's network segments. |
| Vehicle details | Confirm year, two/four doors, trim, engine, factory adaptive cruise, and known relevant modifications or module updates. | Avoids applying conclusions from a different configuration. |

**If you only have time for one thing now, send the adapter photo and FORScan version.** If you already have module screenshots, send those first and include their date. A partial packet is useful. “Unknown” is fine for update history; no dealer visit is needed to fill that in.

## If you have BlueDriver available now

The owner's pictured adapter is a BlueDriver. It can provide a preliminary fault report through its own app: use **Read Codes**, save/share the report, and send any vehicle/module information screens offered. Include module headings and complete codes where available. Leave **Clear Codes** alone to preserve the existing history. BlueDriver's published app description includes Ford enhanced diagnostics and saved/shared reports. [Developer's feature description](https://play.google.com/store/apps/details?id=com.lemurmonitors.bluedriver&hl=en_US).

A fault scan is not a firmware dump. BlueDriver's [Vehicle Identification documentation](https://support.bluedriver.com/en/articles/15108431-vehicle-identification) describes VIN-based identification; it does not establish that the app exposes the GWM/PSCM/IPMA software/calibration identifiers needed here. If those fields are absent, send what you have and collect specific module identification with a compatible FORScan adapter later. Do not spend time trying to make BlueDriver act as an ELM327 adapter. Neither a fault report nor an adapter purchase is required for offline research to continue.

The owner has already supplied Ford's As-Built record, so the next useful file collection is the matching software/data packages or their module-specific file lists. See [the exact download guidance](FIRMWARE_FILE_REQUEST.md). Do not start a vehicle update merely to obtain research inputs.

## Before connecting

Use the adapter you already own as the starting point. FORScan's current guidance cautions that generic ELM327 devices vary in quality and capability. That does not establish whether your particular adapter can complete these identification reads; its exact model matters. We can check that before considering a purchase. [FORScan adapter guidance](https://forscan.org/home.html#elm327_adapters_note).

These information reads do not call for a Windows Extended License, which FORScan associates with functions such as configuration and programming. If you already use FORScan Lite, send what it displays before obtaining different software. [FORScan feature and license overview](https://forscan.org/home.html).

For an adapter that already connects successfully to your Bronco:

1. Park, select Park, apply the parking brake, and keep the engine off. Have the key inside the vehicle.
2. Connect the adapter to the vehicle's OBD diagnostic socket and to your computer/device according to its manufacturer's instructions. Close other diagnostic apps that might use it.
3. Switch on the vehicle's electrical systems without starting the engine. Ford's 2024 Bronco manual calls this accessory mode: from off, press the ignition button once with your foot **off the brake**. Follow the manual supplied with your vehicle if its behavior differs. [Ford's 2024 Bronco ignition instructions](https://www.fordservicecontent.com/Ford_Content/vdirsnet/OwnerManual/Home/Content?ProcUid=G2195550&Uid=G2195549&buildtype=webInstrumentClusterDisplay-UsingtheInstrumentClusterDisplayControls&countryCode=USA&div=f&languageCode=en&userMarket=USA&vFilteringEnabled=False&variantid=9666).
4. Keep the session brief and switch unnecessary accessories off. If you see a low-battery warning, stop the collection and switch the vehicle off. This is not a reason to change battery-saver settings.

If the adapter has never connected successfully, its model and the exact connection error are enough for the first review. There is no need to experiment with wiring, adapter commands, or vehicle settings.

## Collect the identification readout

1. Open FORScan and use its normal **Connect** function. Let detection finish. Use the actual vehicle connection, not demonstration data. Note if the app reused an existing vehicle profile/cache, particularly after a module update.
2. Find the **Vehicle / Vehicle and Interface** information area and its module details or connection log. In the owner's Windows 2.3.68 session, the **Configuration** tab contained the identification text, while **Modules** showed network grouping. Screen labels vary by version. FORScan's Windows documentation describes connection as discovering the adapter, then reading vehicle and module information. Its published full Windows walkthrough is older, so these are task-based directions rather than an exact current button map. [Official Windows connection documentation](https://forscan.org/documentation_13.html).
3. Save or screenshot the information for **PSCM, IPMA, and GWM**. Include each module heading and every identification line. Keep the original labels and punctuation. Several overlapping screenshots of a long log work.
4. Capture the detected-module list and connection warnings. Note the date. Include battery voltage if already displayed; no live-gauge setup is needed.
5. Disconnect in FORScan, switch the vehicle off, and unplug the adapter. Review/redact copies before sharing.

On **FORScan Lite for iOS**, the documented **Vehicle** screen contains adapter, vehicle, and module information; its Save function can export text. Screenshots are equally useful. The About screen also shows the kernel version. Other Lite versions can have a different layout. [Official iOS Vehicle and About documentation](https://forscan.org/documentation_iOS.html).

If the screen looks different or a module is missing, send what you see. Do not open a programming function just to hunt for a missing identifier.

## Which numbers matter?

| Label you may see | What it means for this investigation |
|---|---|
| Part number / hardware number / hardware type | Identification of the module or hardware family; exact meaning depends on the field. Record each separately. |
| Strategy / software identifier | Identifies the operating software and helps locate the relevant firmware version. |
| Calibration / calibration level | Identifies a software or calibration revision, depending on the field. Keep the original label. |
| Other revision fields | Include them if present; no need to decide whether they matter. |
| “Latest known” or an available update | This can describe a candidate update, not what is installed. Capture the installed identification too; do not update anything for the research. |

A similar part-number prefix does **not** establish an exact firmware match. Identification also does not prove the module's full contents or active configuration. We will document a match, mismatch, or uncertainty rather than assume the public firmware's addresses apply to your vehicle.

## Helpful extras, if readily available

- **Existing fault codes:** screenshot the normal DTC readout, especially PSCM, IPMA, GWM, and ABS entries. Include the complete code, suffix, description, and status if shown. Do not clear them or run a self-test to generate more. FORScan distinguishes stored monitoring faults from faults generated by an operator-requested test. [FORScan's diagnostic principles](https://forum.forscan.org/viewtopic.php?f=6&t=2540).
- **Relevant history:** known steering-rack, camera, windshield, or gateway replacements; dealer software updates; prior FORScan changes related to steering, lane assistance, cruise, or networking. “None known” is enough.
- **Factory feature details:** if adaptive cruise or lane-assistance equipment is uncertain, a parked settings-screen or steering-wheel-button photo can clarify it. No driving demonstration is needed.
- **Earlier research:** the exact demonstration video, public development links, or Discord excerpts you are allowed to share, including dates and surrounding context. This can prevent repeating a test whose result was documented privately.

These extras should not delay sending the core identification packet.

## What this collection does and does not do

Here, **read-only** means requesting information without changing configuration or firmware. FORScan still transmits diagnostic requests; this is different from silently listening to the network.

| Term | Plain-English meaning | Needed now? |
|---|---|---|
| Module identification | The computer's displayed hardware/software labels | Yes, to connect the research to your particular vehicle; not to continue offline work |
| DTC | A recorded diagnostic trouble code | Helpful if already available |
| As-Built data | Configuration data describing enabled equipment/options | No; it is not a full firmware dump |
| Firmware dump | A copy of the computer's program/data contents | No dump from your vehicle is requested |
| FORScan PID log | Selected values requested from vehicle computers over time | No; it is not a complete raw network recording |
| Raw CAN / CAN-FD capture | Messages observed on a particular vehicle network segment | Possibly later, with suitable equipment and a separate collection plan |

Reading a steering computer through the OBD port does **not** prove that a normal lane-centering command can travel to it through the same route. Diagnostic access also does not establish raw CAN-FD capture capability. We need to verify the adapter and network location before planning that work. See the project's [delivery milestone](NEXT_STEPS.md#3-establish-message-delivery-with-passive-evidence).

A disconnect during a parked FORScan session would not, by itself, explain the reported openpilot “keep-alive” problem. Record the exact message, approximate elapsed time, and whether the ignition stayed on. Ford documents an accessory battery-saver shutdown; that is a different mechanism from steering-message freshness checks. [2024 Bronco battery-saver note](https://www.fordservicecontent.com/Ford_Content/vdirsnet/OwnerManual/Home/Content?ProcUid=G2195550&Uid=G2195549&buildtype=webInstrumentClusterDisplay-UsingtheInstrumentClusterDisplayControls&countryCode=USA&div=f&languageCode=en&userMarket=USA&vFilteringEnabled=False&variantid=9666).

This guide does not call for **Write/Program**, As-Built edits, firmware updates, module resets, DTC clearing, service procedures, actuator/output tests, or manually transmitted CAN/UDS commands. It does not ask you to enable lane centering or change steering limits. The goal remains the factory interface with its protections intact.

## What can continue without your vehicle?

The [existing investigation](FIRMWARE_INVESTIGATION.md) already traced LMC2 reception and validation in the public sample and checked its checksum arithmetic. The next offline tasks are:

| Work | What it would answer | Vehicle data required to begin? |
|---|---|---|
| Verify the processor decoding used in the next trace | Are the interpreted instructions reliable? | No |
| Follow valid LMC2 data into its consumers | What additional conditions permit or reject lane centering? | No |
| Trace override, arbitration, fault handling, and command limits | Which factory protections govern this path? | No |
| Resolve calibration selection and timer units | Which settings the public firmware uses, and what they mean | No |
| Compare against your installed modules | Does that analysis describe your Bronco's software? | Yes, identification is the first step |
| Establish delivery and real controller behavior | Do commands reach the relevant network segment, and how does the controller respond? | Separate physical evidence; identification alone is insufficient |

The owner information prevents us from confidently solving the wrong firmware version. It is useful early, but **not a prerequisite for the next offline trace**. The full sequence is in [Next steps](NEXT_STEPS.md).

## Copy-and-fill checklist

```text
Collection date:
Vehicle year / full-size Bronco / doors / trim / engine:
Factory adaptive cruise: yes / no / unsure
Relevant modifications or module replacements/updates:

Adapter manufacturer/model:
Connection: USB / Bluetooth / Wi-Fi
HS/MS switch present: yes / no / unsure
Adapter label photo attached:
FORScan version (and kernel version if Lite):
Operating system/device:
Live connection or older saved information:
Existing profile/cache reused, if known:

PSCM identification screenshot/text attached:
IPMA identification screenshot/text attached:
GWM identification screenshot/text attached (or not found):
Full detected-module list attached:
Connection errors or warnings:

Optional existing DTC readout:
Optional relevant development links/excerpts:
```

Redact the **VIN, plate/registration details, names, location, device serial numbers, and license keys** from shared copies. Leave module part, strategy, and calibration identifiers visible. Do not upload raw profiles/debug bundles publicly; they may contain identification beyond one visible screen. Reviewed excerpts can be added to the public repository later. A compact transcription form is also available in [Vehicle information](VEHICLE_INFO.md).
