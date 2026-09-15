# Full-size Bronco: Discord evidence and firmware-source follow-up

Reviewed September 15, 2026. Target: the owner's **2024 full-size Bronco, two-door Badlands Sasquatch, 2.7L, factory adaptive cruise**.

**The review found earlier steering experiments and clearer reasons their results remain inconclusive. It did not establish a safe gateway solution, sustained native LMC2 steering, or a source supplying the owner's exact firmware files.**

This adds authenticated, read-only review of comma.ai's `#ford` channel to the existing [BluePilot website review](BLUEPILOT_SITE_REVIEW.md), [source review](BLUEPILOT_SOURCE_REVIEW.md), [FORScan findings](FORSCAN_FINDINGS.md), and [firmware investigation](FIRMWARE_INVESTIGATION.md). Those analyses are preserved. No Discord messages were posted. No vehicle connection, configuration change, programming, or control test occurred in this follow-up.

## What the earlier attempts demonstrated

Discord links below require appropriate server access. Dates are the displayed message dates; surrounding replies and the current text of edited posts were inspected. A first-person report is evidence of what the tester reported, not an independently reproduced vehicle result. The earlier vehicles' complete hardware, firmware, and calibration sets were not established as matching the owner's Bronco.

| Date and source | Reported observation | What remains unresolved |
|---|---|---|
| [January 21, 2024](https://discord.com/channels/469524606043160576/539096103468007424/1198824820243189920) | A full-size Bronco tester obtained steering using `Lane_Assist_Data1`, the older lane-keeping interface. Steering availability repeatedly dropped, limiting sustained curves. | This demonstrates reported intermittent LKA actuation. It does not demonstrate sustained LMC2 lane centering or validation of factory protections and independent Panda enforcement. |
| [January 25, 2024](https://discord.com/channels/469524606043160576/539096103468007424/1200126392868814938), [January 26–27 context](https://discord.com/channels/469524606043160576/539096103468007424/1200910312774303775) | The tester reported attaching the steering-side CAN-FD network to a reassigned comma bus and seeing additional steering messages. An edited January 26 report asserted that the gateway did not filter LMC1/LMC2, but also reported `sendcan too old to send`. On January 27 the tester clarified that the connector had been modified, with the radar passed through and that bus reassigned near the gateway. | Questions about the default harness's radar bus were answered by that wiring clarification. Correct physical transmission, timing, bus configuration, and receipt of valid commands at the steering controller were not independently established. The tester's suggested traffic-load explanation for the stale-send error remains a hypothesis. |
| [February 23, 2024](https://discord.com/channels/469524606043160576/539096103468007424/1210709137923506196) | The same tester reported observing LMC1 on both sides of the gateway and trying LMC2 directly on the PSCM bus. Later replies described passing other traffic while stopping lane-assist messages; the camera's LMC1 was reportedly never active. | This is a more specific account than a blanket gateway-blocking claim. The review did not obtain synchronized captures proving that valid LMC2 reached the PSCM and was rejected by its application. The January gateway assertion and February account still need reconciliation. |
| [May 13, 2026](https://discord.com/channels/469524606043160576/539096103468007424/1504131320530469026) | A manual-transmission Bronco owner reported a newer LKA build that resumed steering after roughly a second of interruption. The earlier developer replied that interruptions in their current build were momentary and that it deliberately interrupted requests to reduce lockout. | Later software still exhibited LKA interruption. The comparison with older behavior was subjective and disputed in the replies. This is a different vehicle configuration and does not establish a factory LMC2 solution for the owner's Bronco. Timeout-management behavior is outside this project's proposed implementation path. |
| [May 15, 2026](https://discord.com/channels/469524606043160576/539096103468007424/1504967860005503028) | Asked about the earlier gateway test, the original tester recalled seeing CAN traffic but no PSCM response to lane-centering requests. They disclosed using wire taps and Ethernet cable and uncertainty about whether the wiring caused issues. Another participant reported ongoing BluePilot Bronco work and a suspected gateway filter. | The wiring caveat weakens any conclusion that a correctly delivered request was definitively refused by the PSCM. The reported firmware LMC2 path motivates further work; it does not settle routing or steering permission. |
| [June 2, 2026](https://discord.com/channels/469524606043160576/539096103468007424/1511350136675238040) | In direct reply to a full-size Bronco update request, a participant said a custom harness for the CAN-FD side of the gateway had been built and was awaiting a test opportunity. | A secondhand progress report, with no successful test result supplied in that exchange. Nearby reports of other Ford vehicles working must not be attributed to the Bronco. |
| [June 27, 2026 — public forum](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/post-2838452) | The previously documented developer test reported observing LMC2 blocked at the gateway in read-only mode. Direct PSCM injection could not be tested successfully because changing the network connection disrupted termination and caused bus errors. | Stronger firsthand support for filtering in that setup, but no completed test of PSCM acceptance after correct delivery. This existing evidence remains part of the combined record. |
| [August 26, 2026](https://discord.com/channels/469524606043160576/539096103468007424/1542287531960180757) | The most recent substantive full-size Bronco result in the inspected keyword search says it does not work out of the box. It expresses optimism about a custom harness and external red Panda, while describing substantial wiring and software work still needed. | A feasibility opinion based on others' testing. No completed harness specification, matched firmware set, reproducible LMC2 acceptance result, or safety validation accompanies this post. It does not resolve the earlier failures. |

The initial successful steering reports concern **LKA**, the lane-departure-assistance interface. Sustained **LMC2** acceptance is a separate question. A video or report of steering movement cannot, by itself, identify which interface was used or establish its safeguards.

## Gateway, connection loss, and keepalive

The evidence supports separating these failure classes:

| Question | Evidence now available | Useful discriminating evidence |
|---|---|---|
| Does the gateway deliver the relevant message? | The June 27 forum report supports filtering; older Discord accounts differ. | Existing synchronized captures on identified camera-side and steering-side segments, with message identity, timing, source, and configuration documented. Forwarding may depend on message and state. |
| Did a command leave the comma/Panda in time? | The January stale-send error, early uncertainty over selected vehicle profile, and bus reassignment. | Existing send logs and physical receive captures tied to the exact software/Panda build and wiring. A requested transmission or a visible receive message alone is insufficient. |
| Did the steering application permit the request? | Reported LMC2 nonresponse, with unresolved transmission and wiring conditions. The public comparison firmware has a traced LMC2 receive/validation path. | Matched firmware analysis separating arrival, checksum/counter freshness, input selection, arbitration, enable conditions, and final steering authority. |
| Why did steering stop during LKA experiments? | Repeated availability loss and interruptions reported in both 2024 and 2026. | Original traces aligned with steering status and request history. These interruptions must not be relabeled as a gateway disconnect without evidence. |
| Is wakeup or keepalive missing? | The inspected searches did not identify a demonstrated full-size Bronco wakeup/keepalive sequence that fixes LMC2. | Existing startup/sleep captures and firmware dependencies showing a missing condition, followed by evidence that normal factory traffic satisfies it. No arbitrary heartbeat or diagnostic session should be assumed necessary. |

The searches for `wake` and `keep alive` included unrelated power/boot discussions. Those are not evidence for this Bronco. A network being awake, a command being fresh, and steering being authorized are distinct states.

The repository has already traced checksum, counter, arrival, and stale-data handling in the **public comparison PSCM**. Its timer division by 8000 is known, but the counter's physical timebase remains unresolved. That finding must not be converted into a claimed keepalive frequency or a timeout fix. [Existing post-validation findings](POST_VALIDATION_FINDINGS.md).

**Current interpretation:** gateway filtering has firsthand support for the June 27 setup; whether fixing it would be sufficient remains unproven. Permanent lack of steering-firmware support is also unestablished. Delivery and legitimate steering permission remain separate unresolved questions. The direct-bus reports are valuable experiments with incomplete verification, rather than a proven gateway solution.

## Exact firmware acquisition status

All five identifiers below remain established by the owner's connected FORScan session. No matching executable/data file was acquired in this follow-up.

| Module | Exact requested identifier | Result as of September 15, 2026 |
|---|---|---|
| GWM | `MB3T-14H483-FAH` | No matching file source established. |
| PSCM strategy | `RB3C-14D003-AA` | Found as a diagnostic response string in upstream Ford fingerprints and forks; no firmware payload obtained. |
| PSCM calibration | `NB3V-14D004-BF` | No matching file source established. |
| IPMA strategy | `M2DT-14F397-AH` | No matching file source established. |
| IPMA calibration | `M2DT-14F398-AH` | No matching file source established. |

The [pinned upstream fingerprint source](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/fingerprints.py) places `RB3C-14D003-AA` under `FORD_RANGER_MK2`. This is a useful package-provenance lead. It is not an executable, proof of byte identity, or evidence that a Ranger calibration or vehicle profile is appropriate for the Bronco. Repeated copies in forks are not independent firmware acquisitions.

Legitimate acquisition leads, with their limits:

- **Ford's normal service distribution:** the [official subscription-software page](https://www.fordtechservice.dealerconnection.com/Rotunda/MCSIDSDownloadSoftware), inspected September 15, 2026, provides FDRS software. It does not expose or confirm any of these five exact packages. Whether an already-authorized owner or service provider can obtain these historical revisions without starting a programming operation is unverified. A software installer is not the required module firmware.
- **An existing, lawfully obtained module package or cached manifest:** the [source project's downloader](https://github.com/ghostdev137/ford-pscm-re/blob/f545afe509aa936a32ad026d411add394f8464ae/tools/ford_download.py) documents using cached FDRS application manifests. This project still has no matching Bronco manifest. Existing files or a sanitized module file list, supplied by someone entitled to share them, are a more concrete lead than guessing public filenames.
- **Public research archives:** the [existing comparison source](https://github.com/ghostdev137/ford-pscm-re/tree/f545afe509aa936a32ad026d411add394f8464ae) was rechecked. It still does not supply the requested exact filenames. Its [FDRS MDX archive description](https://github.com/ghostdev137/ford-pscm-re/blob/f545afe509aa936a32ad026d411add394f8464ae/firmware/_fdrs_archive/README.md) describes diagnostic definitions, not the owner's GWM/PSCM/IPMA executable set. An older firmware-repository link found in Discord returned GitHub 404; it yielded no files.

Each exact identifier returned no `#ford` search results. Public GitHub code searches returned fingerprint entries for the PSCM strategy and no hits for the other four identifiers; indexed web searches did not establish a matching downloadable file. Search indexing is incomplete, so these are bounded negative findings.

The failed public calibration-portal filename attempts were **not repeated**. Their failure does not prove that Ford never distributed the files or that a vehicle security mechanism is involved. The [existing exact-file request](FIRMWARE_FILE_REQUEST.md) also identifies companion configuration/data items needed to understand a complete module package.

No new firmware manifest, executable, calibration, or checksum inventory was created because no matching files were obtained. No subscriptions were bought, credentials shared, or programming sessions initiated.

## Retained protections and the BluePilot concern

The earlier [independent safety-code check](BLUEPILOT_SITE_REVIEW.md#independent-safety-code-check) remains material. It reported that the inspected BluePilot C transmit policy enforced a control-permission rejection in a baseline case but failed to enforce it in a reset-related host-test case, with and without the debug flag.

The previously reviewed snapshots are `bp-7.0` at `e1d051d7ba270261b4455068bd68f1a58db15a4a` and `bp-dev` at `e22afa6be9b881fa784c92ebb316db47728a3d81`; their inspected Ford safety headers were identical. The development branch was rechecked during this follow-up and remained at that same revision. This follow-up did not rerun or broaden the host test.

This is a software-policy finding, not a demonstration of steering movement or defeat of Ford's EPS protections. A fix and independent review have not been established here. Accordingly, the inspected branch still cannot be recommended as satisfying this project's Panda-safeguard requirement. No issue or message was sent to the other project.

A native gateway harness, a firmware timeout modification, and a torque-sensor interceptor are different proposals. The [complete website review](BLUEPILOT_SITE_REVIEW.md) already explains why a Bronco entry in an interceptor compatibility table does not establish a working native LMC2 port. Factory watchdogs, steering bounds, driver override, and independent Panda checks remain requirements.

## Next useful work

1. **Obtain existing evidence before another experiment.** Seek an already-existing, shareable package or sanitized manifest for the exact identifiers. For earlier tests, the useful missing materials are a wiring diagram, complete software/build identities, paired captures, send/receive timestamps, and error/status history. No outreach is authorized or performed in this review.
2. **Reconstruct the earlier tests offline.** Determine which profile selected LMC2, which bus the code targeted, what Panda accepted or rejected, and when the stale-send condition arose. Match that to actual steering-side observations and the later harness/termination evidence. The goal is to distinguish “requested,” “transmitted,” “received,” and “accepted.”
3. **Continue the factory-permission trace.** Use the existing public sample only as a comparison until matched bytes arrive. Follow remaining status-mask conditions, arbitration, driver override, limits, fault handling, and timing dependencies; record what each condition actually proves.
4. **Keep safety review a separate gate.** Tie any proposed controller to an exact Panda build and independent policy verification, including controls-disabled, reset, stale-input, disengagement, and driver-override behavior. A routing improvement cannot resolve an independent safety-policy failure.
5. **Reassess hardware only after those results.** A proposed bench/harness design would need accurate protocol, topology, termination, normal wakeup, and fault behavior. The current record does not justify a wiring purchase, a vehicle write, watchdog changes, or installation on this Bronco.

The owner's identification step is complete. Another FORScan identification scan would not fill the missing firmware or delivery evidence. Factory ACC remains the intended initial longitudinal behavior if a future lateral-only port proves feasible.

## Review coverage and limits

- Read all **275 distinct results across 11 pages** for `in:ford Bronco`, spanning June 3, 2020 through September 6, 2026. The latest results concern Bronco Sport and were excluded from full-size conclusions.
- Read all returned results for `LMC2` (10), alternate spelling `LCM2` (6), `"direct connection"` (8), `wake` (4), `"keep alive"` (3), `vbf` (17), and `FDRS` (35 across two pages), all scoped to `#ford`. `keepalive` returned none.
- Inspected the newest 25 of 90 `gateway` results, then focused date-filtered results and original message contexts for the relevant Bronco exchanges. The entire gateway search was not reviewed.
- Rechecked the previously cited Bronco6G discussion, pages 29–30, including the June 27 first-person test report. The inspected later page did not establish a gateway solution.
- Searched each of the five exact firmware identifiers separately in `#ford` and public GitHub code search; checked public web results and the previously used source inventory.
- Search results and selected surrounding message history were read. Private drive logs, attachment contents, and developers' physical setups were not independently validated. No claim is made to have exhausted other servers, private threads, unindexed attachments, or deleted messages.

This report contains paraphrases and source links. It excludes VINs, private device/route identifiers, raw owner records, and raw Discord conversations.
