# Read-only vehicle-information worksheet

For the beginner walkthrough, equipment checklist, and explanation of what can continue without vehicle data, start with the [owner collection guide](OWNER_COLLECTION_GUIDE.md).

The first useful vehicle input is identification information. A firmware file found online may describe a different steering-computer revision from the one installed in the target Bronco.

Using FORScan's module-information readout, save the displayed identifiers for the modules below. Screen names vary by FORScan version. This task is limited to reading information; it does not require configuration changes, programming, actuator tests, or clearing faults. Module-information queries are read-only diagnostic requests, which are different from a purely passive network capture.

| Module name | Plain-English meaning | Information to record if displayed |
|---|---|---|
| PSCM — Power Steering Control Module | Steering computer | Hardware/part number, strategy/software identifier, calibration identifier, other displayed revision fields |
| IPMA — Image Processing Module A | Windshield-camera processing module | Hardware/part number, strategy/software identifier, calibration identifier |
| GWM — Gateway Module | Connects vehicle network segments | Hardware/part number, strategy/software identifier, calibration identifier |

Also record:

- Model year and full-size Bronco body style: two-door or four-door.
- Trim, factory adaptive-cruise equipment, and any known steering/camera/gateway replacements or software updates.
- FORScan version and operating system.
- Exact OBD adapter manufacturer/model and connection type.
- The date of the readout. If a field is absent, write “not displayed” instead of guessing.

A screenshot or transcribed table is enough to start. Redact the VIN, registration/owner details, device serial numbers, and unrelated personal information before sharing. Keep raw diagnostic profiles or captures outside the repository unless deliberately reviewed for publication. The repository ignores a `private_vehicle_data/` directory for local working copies.

## Fill-in template

```text
Readout date:
Model year / body style / trim:
Factory ACC:
Relevant module replacements or updates:
FORScan version / operating system:
Adapter manufacturer / model / connection:

PSCM hardware / part number:
PSCM strategy / software:
PSCM calibration:

IPMA hardware / part number:
IPMA strategy / software:
IPMA calibration:

GWM hardware / part number:
GWM strategy / software:
GWM calibration:
```

The next analysis step is to compare these identifiers with the pinned public sample. This worksheet does not identify a required FORScan configuration change.
