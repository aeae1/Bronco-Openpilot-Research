# Owner FORScan identification and network grouping

September 15, 2026. The owner supplied Configuration-tab text and Log/Modules screenshots from FORScan 2.3.68 on Windows during a connected session. Selected fields were transcribed into [the identification record](../results/owner_forscan_identification.json). Raw screenshots, VINs, the adapter serial, odometer, and unrelated module data are excluded.

**The identification collection is complete for this step. All three displayed strategy identifiers match the As-Built record. No matching executable firmware has been acquired, and gateway delivery remains unresolved.** Reuse of a saved FORScan profile/cache was not established; this is evidence of the reported identification during a connected session, not independent verification of installed program bytes.

## Compared identifiers

| Module | FORScan Part number | FORScan Strategy | FORScan Calibration | Comparison with As-Built |
|---|---|---|---|---|
| GWM | `RU5T-14H474-FAH` | `MB3T-14H483-FAH` | Not displayed | Part and strategy match |
| PSCM | `NB3V-3F964-BF` | `RB3C-14D003-AA` | `NB3V-14D004-BF` | All three match |
| IPMA | `M2DT-19H406-CH` | `M2DT-14F397-AH` | `M2DT-14F398-AH` | All three match |

These are eight matching field comparisons: three part numbers against As-Built F113, three strategies against F188, and two calibration identifiers against F124. FORScan's separate `Calibration level` line repeats the part number in these three entries; it must not be mistaken for an additional program or calibration-data filename.

The extra gateway calibration/configuration identifiers, PSCM Cal-Config, and camera second program/data entries from [As-Built](ASBUILT_FINDINGS.md) were not displayed here. Do not describe the entire ten-file candidate set as confirmed by this read.

The PSCM strategy still differs from the analyzed public `NB3C-14D003-AB` sample. Its displayed calibration is `NB3V-14D004-BF`, whereas the analyzed sample used `NB3C-14D004-AD`. The earlier static traces and selected virtual execution remain specific to that public sample. The matching owner program/data files are needed before carrying those findings over.

## What the Modules screen adds

| Target | Group displayed by FORScan |
|---|---|
| GWM | HSCAN |
| PSCM | CANFD |
| IPMA | HSCAN2 |

The camera and steering classifications are consistent with the network separation discussed in earlier Bronco development attempts. This is a diagnostic application's classification, not an independently measured wiring diagram or packet trace. The gateway's own HSCAN listing does not mean it serves only that network.

The connection discovered all three targets and returned the identification above. It does not establish that a normal lane-centering message crosses the gateway, nor that the ELM adapter can directly capture or transmit CAN-FD frames. No message-forwarding rule, keep-alive requirement, or cause of prior development failures was established by these screens.

## Adapter and session limits

The owner identified an OHP ELMconfig USB adapter with a manual HS-CAN/MS-CAN switch. FORScan reported ELM327 v1.4, a 500000 bps interface link, minimum delay of 3 ms, and two CAN errors (1.0%). It warned that this adapter is not recommended for this car and that some functions may be unavailable or unreliable. The reported link speed is not a measurement of every vehicle network's bitrate.

The screenshots displayed 11.9 V. The owner was advised to keep collection brief and disconnect/switch the ignition off afterward. These observations do not identify the cause of the CAN errors, establish battery health, or validate the adapter for programming or openpilot use. No programming, configuration changes, code clearing, or driving test was requested.

## Firmware download follow-up

The owner reached Ford Service Info's Calibration Files web form. Screenshots show the exact gateway request failing both with `.VBF` and without it. The page appended `.ZIP`, reporting `File name invalid or not found` for `MB3T-14H483-FAH.VBF.ZIP` and `MB3T-14H483-FAH.ZIP` respectively. Removing the extension did not solve it.

After being asked to try gateway configuration `MB3T-14H485-FAG` and steering software `RB3C-14D003-AA`, the owner reported no success with any filename. These additional failures are owner-reported; their individual response bodies were not provided. This web-form result is separate from the earlier automated endpoint's ASP server error. Neither establishes that the vehicle uses an unbreakable security barrier, or that the packages cannot exist in another authorized Ford distribution channel.

Do not repeat the same filename guesses without new evidence. An existing matching vendor package or module-specific FDRS package list remains the next acquisition lead. No download-only FDRS route for these exact revisions has been verified, so a subscription purchase is not justified by this investigation. [Exact identifiers](FIRMWARE_FILE_REQUEST.md).

Offline steering analysis can continue using the existing public samples. Investigating the owner's gateway program requires a usable executable and relevant data; obtaining these would still not constitute a working virtual vehicle or a safe openpilot port.
