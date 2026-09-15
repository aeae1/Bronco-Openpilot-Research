# Gateway firmware search and additional comparison files

Research continued September 14–15, 2026. Status checked September 15, 2026.

**Follow-up:** the owner has now supplied the As-Built record. The gateway software is listed as `MB3T-14H483-FAH`; steering is `RB3C-14D003-AA`, different from the sample already analyzed. See [the new identification findings](ASBUILT_FINDINGS.md) and [precise file request](FIRMWARE_FILE_REQUEST.md). The acquisition attempts below are preserved as history.

**No executable firmware matched to the owner's Bronco gateway has been obtained.** Eight additional public files have been downloaded and checked for offline comparison: camera and steering firmware from other Ford vehicles, plus gateway and camera diagnostic definitions. None is established as software installed in the owner's 2024 full-size Bronco.

## September 15 Discord and exact-identifier follow-up

The [new dated review](DISCORD_FORD_REVIEW.md#exact-firmware-acquisition-status) searched each of the five FORScan-confirmed identifiers in comma.ai #ford, public GitHub code search, and indexed web results. No matching firmware file or Bronco-specific manifest was obtained. The failed public calibration-portal filename attempts were not repeated.

`RB3C-14D003-AA` appears in the [pinned upstream Ranger MK2 diagnostic fingerprints](https://github.com/commaai/opendbc/blob/057aee25b5eee7530f0b95b5b508c8c3247b0cd7/opendbc/car/ford/fingerprints.py). That is an identification/provenance lead, not firmware or evidence of matching calibration. Searches did not establish file sources for `MB3T-14H483-FAH`, `NB3V-14D004-BF`, `M2DT-14F397-AH`, or `M2DT-14F398-AH`.

Ford's [official service-software distribution page](https://www.fordtechservice.dealerconnection.com/Rotunda/MCSIDSDownloadSoftware) supplies FDRS software but does not establish availability of these exact historical packages. An existing, lawfully obtained module package or sanitized FDRS manifest remains the concrete acquisition lead. No paid access, account sharing, programming session, or new vehicle scan was initiated. The comparison source was rechecked and still does not provide the exact requested filenames.

## What is available now

The existing Bronco steering set remains `NB3C-14D003-AB`, `NB3C-14D004-AD`, and `NB3C-14D007-AAB`, documented in [the original investigation](FIRMWARE_INVESTIGATION.md).

All eight new files come from [ghostdev137/ford-pscm-re at revision f545afe](https://github.com/ghostdev137/ford-pscm-re/tree/f545afe509aa936a32ad026d411add394f8464ae). Exact paths, sizes, SHA-256 hashes, and Git blob identities are in [the download manifest](../module_firmware_manifest.json).

| Acquired files | Contents | Relevance and limit |
|---|---|---|
| `NK3T-14F397-AB.VBF`, `NK3T-14F398-AC.VBF` | Camera application and calibration. Headers identify RH850, diagnostic address `0x706`, and uncompressed data. | Comparison candidates from the source's `Transit_2025` collection. Exact donor vehicle and compatibility with Bronco IPMA are unverified. |
| `H1BT-14F399-AB.VBF` | Small RH850 flash driver, type `SBL`, at address `0x706`. | Retained for inventory completeness. It is not the camera's normal application and will not be run. |
| `ML3V-14D003-BD.VBF`, `ML34-14D004-EP.VBF`, `ML34-14D007-EDL.VBF` | Steering application and two data containers at diagnostic address `0x730`. | Source labels this a 2021 F-150 Lariat BlueCruise set. Useful for comparing application structure and checks; no cross-flashing or compatibility claim. |
| `716_GWM.xml` | Ford-format MDX diagnostic definitions, UID `G2472482`, with 209 DID definitions. | Source attributes this to a 2025 Transit Custom diagnostic session. **Not gateway executable code or a dump of the owner's gateway.** |
| `706_IPMA.xml` | MDX diagnostic definitions, UID `G2427628`, with 322 DID definitions. | Camera diagnostic reference from that source session; not executable code or actual identification responses. |

The upstream [firmware inventory](https://github.com/ghostdev137/ford-pscm-re/blob/f545afe509aa936a32ad026d411add394f8464ae/docs/firmware-versions.md) and [diagnostic inventory](https://github.com/ghostdev137/ford-pscm-re/blob/f545afe509aa936a32ad026d411add394f8464ae/analysis/transit/diagnostics/module_inventory.md) provide donor attributions, not independent identification. The camera firmware folder and Transit Custom diagnostic collection are not assumed to be a matched set.

## Verification

- Eight files totaling **9,886,594 bytes** match their blobs in the immutable upstream Git tree. SHA-256 hashes are recorded for repeatable retrieval.
- Six VBF containers parse successfully. All **nine block CRC-16 values** and all **six file CRC-32 values** match.
- Both XML files parse as MDX diagnostic documents. Their identification fields define information a scanner may request; they are not values returned by the owner's vehicle.
- The inspector correctly rejected the actual Ford server-error response and a single-byte corruption made only in memory for verification.

These checks establish file integrity, not a Ford-approved release or installation compatibility. Two F-150 headers describe their contents as “Unsigned”; no cryptographic signature was independently verified for any sample.

The [inspection results](../results/module_firmware_inventory.json) record header fields, block addresses/hashes, checksums, and selected diagnostic labels. VBF `CAN_STANDARD` header text concerns programming-container metadata; it does not establish the vehicle's complete runtime CAN/CAN-FD topology.

## Gateway download attempts

An older Ford download workflow is documented in [incognitojam/op-notebooks](https://github.com/incognitojam/op-notebooks/blob/1109fbdb25e3bdb7bfb7033a56bba7338bb60688/ford/download_vbf.py). Its [historical inventory](https://github.com/incognitojam/op-notebooks/blob/1109fbdb25e3bdb7bfb7033a56bba7338bb60688/ford/data/vbf/vbf.json) lists gateway-numbered files including `M1GT-14F530-BB.VBF` as previously downloaded.

Two requests for that listed file to the documented Ford service returned HTTP 200 with the same **1,172-byte ASP server-error body**, not a ZIP or VBF. The error included `Server.CreateObject Failed`. Response SHA-256: `6283acb39ff988b7842ad6881b63f2fe6e148f0f0f3ee1a9ef0c8ad106224467`. This was a service-availability check using a published filename, **not a Bronco firmware match**. The response was rejected as firmware.

The source project's [FDRS downloader](https://github.com/ghostdev137/ford-pscm-re/blob/f545afe509aa936a32ad026d411add394f8464ae/tools/ford_download.py) describes obtaining URLs from already-cached FDRS application manifests. We do not have a Bronco-specific manifest. Its alternative URL construction was not used. No credentials, CAPTCHA replay, or access-control workaround were used in this investigation.

Other public archives inspected did not provide a verified Bronco gateway executable. This bounded search result is not proof that no copy exists. A failed download also does not establish a security barrier in the vehicle.

## VIN and As-Built lookup

The owner supplied a VIN privately. It passes the standard check-digit calculation. Navigation to [Ford's As-Built lookup](https://www.motorcraftservice.com/AsBuilt) returned a `502 Bad Gateway` page stating that certificate verification failed, including after one browser reload. The form was not reached and no VIN query was submitted. This is an access failure from this environment, not a vehicle-not-found result.

**Completed by the owner:** the downloaded As-Built record is now available privately and its selected module identifiers have been extracted. No further As-Built download is needed. The later FORScan identification read has also been received and matches the three main strategies. [Connected-session results and subsequent unsuccessful owner web downloads](FORSCAN_FINDINGS.md).

An As-Built record may include module software identifiers, but it is **not executable firmware**. Treat its identifiers as factory-record evidence until compared with live module identification; updates or replacements can change what is installed. The VIN and raw owner records are excluded from the public repository.

## Other useful owner-held files

| Material | Use |
|---|---|
| Existing Ford `.vbf` files or update ZIP for GWM/IPMA/PSCM | Actual offline analysis candidates. Include source and download date. |
| Matching module-specific FDRS file list or manifest excerpt | Helps identify which program/data files belong together and their intended module. |
| Complete GWM, PSCM, and IPMA identification screenshots | Hardware, strategy/software, and calibration identifiers with all suffixes. [Collection guide](OWNER_COLLECTION_GUIDE.md). |
| Development attachments shared with permission | Firmware or observations missing from public sources; retain provenance and date. |

The MDX references define core assembly (`F111`), delivery assembly (`F113`), and manufacturer software number (`F188`); the camera reference also defines calibration data number (`F124`). These are reference labels for interpreting exports, not instructions to send manual diagnostic commands or a promise that every field exists in the owner's modules.

Send files in chat for review instead of committing raw diagnostic bundles publicly. Redact VINs, account details, device serial numbers, license keys, and authenticated/token-bearing URLs from excerpts. Leave module software/part identifiers visible. As-Built `.ab`/`.abt` files can carry configuration and sometimes identity information, but do not replace executable firmware.

There is no need to buy an FDRS subscription, initiate a vehicle update, or open a programming routine solely for this collection. Exact identifiers will let a subsequent request name a specific file/package. If its normal download requires owner access, the exact item and access limitation will be explained first.

## Next analysis and reproduction

The Bronco steering trace can continue immediately. The F-150 set offers comparison material for application logic. The camera set offers a candidate for studying factory lane-assistance message construction after its architecture and relevance are checked. These are future analysis opportunities, not newly proven behavior.

A matched gateway executable and relevant data/configuration are still needed to examine forwarding logic from firmware. Selected function checks would not be a full virtual gateway: boot state, configuration, peripherals, and timing may need modeling and comparison with observations. No gateway connection fix or vehicle safety result follows from these downloads.

From the repository root:

```bash
python3 fetch_module_firmware.py
python3 inspect_module_firmware.py
```

For a recheck without network access:

```bash
python3 fetch_module_firmware.py --verify-only
python3 inspect_module_firmware.py
```

Expected: eight matching files, six VBF containers, nine matching block checksums, and six matching file checksums. Raw downloads remain under ignored `sources/`; the repository stores manifests, inspection results, and original analysis tools.
