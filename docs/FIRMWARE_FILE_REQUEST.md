# Exact firmware identifiers to request

September 15, 2026. These identifiers come from the owner's Ford As-Built record. [Interpretation and limits](ASBUILT_FINDINGS.md).

**Request existing, unmodified vendor files for offline analysis. This is a download request, not an instruction to program a vehicle.** No matching executable files in this table have been acquired yet. **Owner FORScan identification now matches the three main strategies and the two displayed calibration-data identifiers. The public download form failed for the gateway with and without the extension; further requested names also failed according to the owner. Do not repeat that route without new evidence.** [Session findings](FORSCAN_FINDINGS.md). The identifiers are established; the `.VBF` filenames below are candidates, not confirmed available downloads. A provider may distribute them inside another package format.

| Priority | Module | Recorded purpose | Identifier / candidate VBF filename |
|---|---|---|---|
| 1 | GWM | Main software (`F188`) | `MB3T-14H483-FAH.VBF` |
| 1 | GWM | Cal-Config (`F10A`) | `MB3T-14H485-FAG.VBF` |
| 1 | GWM | Cal-Config #3 (`F16C`) | `MB3T-14H484-FAG.VBF` |
| 2 | PSCM | Main software (`F188`) | `RB3C-14D003-AA.VBF` |
| 2 | PSCM | Calibration data #1 (`F124`) | `NB3V-14D004-BF.VBF` |
| 2 | PSCM | Cal-Config (`F10A`) | `NB3C-14D007-AHD.VBF` |
| 3 | IPMA | Main software (`F188`) | `M2DT-14F397-AH.VBF` |
| 3 | IPMA | Software #2 (`F120`) | `M2DT-14F397-BD.VBF` |
| 3 | IPMA | Calibration data #1 (`F124`) | `M2DT-14F398-AH.VBF` |
| 3 | IPMA | Calibration data #2 (`F125`) | `M2DT-14F398-BD.VBF` |

The accompanying module-specific package list or manifest is valuable because it can explain required companion files and which part is program code versus configuration. Preserve the source and download date. A list alone is useful if the underlying download is unavailable.

An assembly identifier such as `RU5T-14H474-FAH` identifies the module assembly; do not substitute it for the software identifier. Do not request `XXXX-14H525-XXX`: it is a placeholder in the record. The `DS...` identifiers describe diagnostic specifications rather than the module's executable program.

The legacy Ford download endpoint returned an ASP server error here for the exact gateway candidate. That does not distinguish an unavailable part from a broken service. If an existing Motorcraft/FDRS account or normal vendor download page can retrieve these files, use that authorized route. No subscription purchase, account sharing, programming session, or vehicle connection is needed for the current request. If only a paid route is offered, record the option before spending money.

Keep raw owner records, VINs, credentials, license keys, and token-bearing download URLs private. Firmware files are ignored by this repository; analysis results can record verified hashes and non-sensitive provenance after inspection.
