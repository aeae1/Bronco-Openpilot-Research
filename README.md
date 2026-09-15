# Bronco openpilot research

![Bronco openpilot research: the original Bronco illustration beside a sage road graphic and upright Rubik Black title](assets/readme-banner.png)

Can a **2024 full-size Ford Bronco** use openpilot through Ford's factory lane-centering interface while retaining factory steering protections and independent Panda safety checks?

**Status: offline research, September 14, 2026. No working vehicle port or validated installation is available here.** The full-size Bronco is absent from the [upstream Ford definitions inspected](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/values.py). The Bronco Sport is a different vehicle.

## What we found

A publicly posted Bronco steering-computer firmware sample contains a real receive and validation path for **LMC2**, the lane-centering message used by openpilot on some supported Fords. The investigation followed that path beyond the list of message IDs and compared its checksum arithmetic with upstream opendbc: **10,640 software comparisons, zero mismatches**.

That gives us a concrete place to continue. It does not yet tell us whether the owner's installed steering computer has the same firmware, whether its network gateway delivers the message, or whether the steering application permits sustained lane centering.

| Question | Current evidence |
|---|---|
| Does the public sample recognize LMC2? | A traced receive path, arrival tracking, checksum/counter handling, and stale-data handling are present. |
| What did this investigation add? | A corrected receive-table interpretation, a mapped internal route, a checksum comparison, and a trace into application consumers and startup input selection. |
| Does this explain the reported connection problem? | No. Delivery through the gateway and acceptance inside the steering computer remain separate unresolved questions. |
| Can this Bronco safely run openpilot now? | This research does not establish that. No vehicle testing was performed. |
| Must we defeat a security system? | Nothing in the traced receive/checksum path establishes that requirement. Other activation or security conditions have not been ruled out. |

**New follow-up:** the trace now reaches application code that consumes LMC2 path data. The sample's startup defaults select its LMC2 input branch, confirmed by targeted virtual-memory checks. Its validity state also participates in broader application status checks. Read [the new findings and their limits](docs/POST_VALIDATION_FINDINGS.md). Selecting an input source is still separate from permitting steering.

## Start here

- [Gateway firmware search: acquired files, limits, and useful owner downloads](docs/FIRMWARE_ACQUISITION.md)
- [New findings: application consumers, startup selection, and remaining gates](docs/POST_VALIDATION_FINDINGS.md)
- [Owner guide: what to collect with FORScan and your OBD adapter](docs/OWNER_COLLECTION_GUIDE.md)
- [Plain-English explanation and comparison with earlier attempts](docs/PLAIN_ENGLISH.md)
- [Next steps, with evidence needed for each milestone](docs/NEXT_STEPS.md)
- [Vehicle-information worksheet](docs/VEHICLE_INFO.md)
- [Full firmware investigation and source citations](docs/FIRMWARE_INVESTIGATION.md)
- [Reproduce the offline checks](docs/REPRODUCING.md)
- [Source provenance and credits](THIRD_PARTY.md)

## Why a standalone repository?

This repository keeps the evidence, scripts, uncertainties, and next tasks together, with a change history other developers can review. A repository is useful for continuing and sharing the work; creating one does not make the vehicle compatible.

A fork of opendbc/openpilot becomes useful when there is a specific implementation to develop. The immediate work is establishing the factory interface and its conditions. No openpilot fork is maintained here yet.

## Research boundary

The intended direction retains Ford's steering authority limits, supervision, driver override, and fault handling, plus independent Panda command checks. Factory adaptive cruise control is the intended starting point for any future lateral-control port.

This project contains local file-analysis scripts. It has no adapter connection, CAN transmitter, firmware flasher, torque interceptor, or code to defeat a timeout. Raw firmware, downloaded third-party source, private vehicle records, and large tool installations are excluded from version control.

## Reproduce

From the repository root, with Python 3.10 or newer and network access:

```bash
python3 fetch_firmware.py
python3 fetch_port_sources.py
python3 analyze_firmware.py
python3 check_checksum.py
python3 analyze_followup.py
```

Expected: four firmware-related files match pinned hashes; all six VBF block CRCs pass; two receive arrays contain 62 records each; 10,640 checksum comparisons match. These checks concern static data and arithmetic, not vehicle behavior. See [the reproduction guide](docs/REPRODUCING.md) for Ghidra setup and decoder limitations.

The initial investigation was prepared with ChatGPT/Codex for the repository owner. It builds on public work by ghostdev137, comma contributors, mims002, and developers documenting Bronco experiments. Independent findings here do not establish that nobody has made the same findings privately. Private Discord channels were not inspected.
