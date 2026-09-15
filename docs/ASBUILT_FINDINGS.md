# What the owner's As-Built record adds

September 15, 2026. Source: the owner-supplied Ford As-Built file. The raw file and VIN remain private; [the extracted identification](../results/owner_asbuilt_identification.json) contains only selected module part/software identifiers.

**The file supplies the gateway, steering, and camera identifiers needed to focus the firmware search. It also shows that the steering software in this record differs from the sample analyzed so far.** These are server-record identifiers, not a live scan of the installed modules.

## Three relevant module records

The XML parses successfully and contains 30 module nodes and 933 configuration-data rows. All three target module nodes are present.

| Module | Delivery assembly (`F113`) | Main software (`F188`) |
|---|---|---|
| GWM — gateway, node `716` | `RU5T-14H474-FAH` | **`MB3T-14H483-FAH`** |
| PSCM — steering, node `730` | `NB3V-3F964-BF` | **`RB3C-14D003-AA`** |
| IPMA — camera, node `706` | `M2DT-19H406-CH` | **`M2DT-14F397-AH`** |

The gateway's core assembly identifier (`F111`) is `RU5T-14H475-AAD`; the steering module's is `MB3C-14F079-BB`; the camera's is `M2DT-14F403-CD`. These are identification fields, not evidence of processor type, board layout, or interchangeable hardware.

The file also lists:

- **Gateway:** Cal-Config `MB3T-14H485-FAG` (`F10A`) and Cal-Config #3 `MB3T-14H484-FAG` (`F16C`). The `F16B` entry `XXXX-14H525-XXX` is a placeholder, so it is excluded from download requests.
- **Steering:** data #1 `NB3V-14D004-BF` (`F124`) and Cal-Config `NB3C-14D007-AHD` (`F10A`).
- **Camera:** software #2 `M2DT-14F397-BD` (`F120`), calibration #1 `M2DT-14F398-AH` (`F124`), and calibration #2 `M2DT-14F398-BD` (`F125`). Multiple software/data entries should be retained together; their processor roles have not been established.

The JSON preserves the original diagnostic identifiers. Descriptive labels were cross-checked against the public Ford-format MDX references acquired earlier. Those references are not proven to be the exact diagnostic specifications for these modules. The record separately identifies its diagnostic specifications as `DSPU5T-14H474-FAA` (GWM), `DSPB3C-3F964-AA` (PSCM), and `DSM2DT-19H406-AB` (IPMA); those identifiers are not firmware binaries.

## Consequence for the earlier steering analysis

| Component | Sample analyzed | Owner's As-Built record | Exact identifier match? |
|---|---|---|---|
| Main software | `NB3C-14D003-AB` | `RB3C-14D003-AA` | No |
| Data #1 | `NB3C-14D004-AD` | `NB3V-14D004-BF` | No |
| Cal-Config | `NB3C-14D007-AAB` | `NB3C-14D007-AHD` | No |

The receive-path, checksum, application-consumer, and startup-selection findings still describe the exact public sample on which they were measured. They cannot be carried over as verified addresses or behavior for `RB3C-14D003-AA`. Obtain the matching program/data files and repeat the relevant checks; a live identification read will establish whether the server record describes the installed modules.

There is a useful comparison lead: upstream opendbc's [Ford firmware database at revision 057aee25](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/fingerprints.py) lists **both `NB3C-14D003-AB` and `RB3C-14D003-AA`** as steering ECU responses under `FORD_RANGER_MK2`. The same revision's [platform definition](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/values.py) describes the 2024 Ranger with adaptive cruise and lane centering and uses its Ford CAN-FD configuration.

This links the identifiers to another relevant Ford platform. It is **not a firmware download**, does not compare the underlying bytes, and does not establish identical steering hardware, calibration, gateway routing, or Bronco support. A shared steering identifier does not solve delivery through the gateway.

The [comparison record](../results/owner_asbuilt_comparison.json) records the upstream revision/hash and the three sample mismatches. The upstream Python file was parsed as data; it was not executed.

## Firmware search result

Exact-identifier public code searches did not locate matching gateway or camera binaries, or a binary for the recorded steering version. The steering-software hits were identification lists. Searches are bounded and cannot establish that no public copy exists.

A request for the exact gateway candidate `MB3T-14H483-FAH.VBF` to the previously documented Ford download service returned HTTP 200 with the same 1,172-byte ASP error body seen earlier. The response was not a ZIP or VBF; its SHA-256 is recorded in the comparison JSON. No matching executable firmware was obtained in this step.

The gateway search can now focus on `MB3T-14H483-FAH` and its associated data instead of generic `14F530` examples from other Ford platforms. The exact identifiers alone do not reveal whether the blocking mechanism is a route table, state requirement, security check, or something else.

## What to collect next

The [precise firmware-file request](FIRMWARE_FILE_REQUEST.md) lists ten software/data identifiers, with the gateway's three files first. They can be sought as normal vendor downloads or existing authorized update packages, without a vehicle connection. Their availability and container filenames are not yet verified.

The As-Built file is sufficient to begin that targeted search. A later read-only FORScan identification report remains useful to compare installed GWM/PSCM/IPMA versions against this record. BlueDriver fault reports are optional and do not substitute for those software identifiers. No firmware extraction from the physical module or programming session is requested.

The two `ERROR` sections in the file say `PCM DATA NOT FOUND` and `CCC DATA NOT FOUND`. They describe absent sections in this record; they are not a live DTC scan and should not be interpreted as new vehicle faults. The target identification nodes are present despite those messages.

## Reproduce the private-file extraction

With an authorized local copy under the ignored `private_vehicle_data/` directory:

```bash
python3 analyze_asbuilt.py private_vehicle_data/owner_asbuilt.ab --output results/owner_asbuilt_identification.json
```

The extractor allows only selected part/software fields for nodes `706`, `716`, and `730`. It omits VINs, serial numbers, manufacturing codes, raw configuration bytes, the source filename, and the source-file hash. The published subset cannot independently authenticate the private source record.
