# BluePilot website review

Reviewed September 15, 2026. This expands the [initial article review](BLUEPILOT_SOURCE_REVIEW.md). It does not establish a working or safe full-size Bronco port.

## Coverage

The live [announcement archive](https://bluepilot.dev/announcements/) contained **34 entries across four pages**. Its list and expanded articles load asynchronously. The review covered the listed article text, the homepage, FAQ, both hardware order pages, and relevant linked source code. The dock-maintenance entry contains an embedded video rather than explanatory text; its embed was identified. This was not a comprehensive review of every embedded video, external forum, or private conversation.

The [source inventory](../results/bluepilot_site_inventory.json) records every archive entry and its displayed date. Dates are publication labels, not reliable revision dates: several older pages contain newer edits. An expanded archive article supplied the tuning text when a direct-link extraction returned an unrelated video.

## What is specifically about the full-size Bronco?

The June interceptor article contains a **vehicle table embedded as an image**. It labels the sixth-generation Bronco confirmed, but its caption defines confirmation as validation of the **sensor architecture**. The article describes an F-150 bench prototype and future product-development work. This establishes a relevant hardware research lead; it does not establish a Bronco installation, driving validation, or preservation of factory ADAS restrictions. [Article and vehicle table](https://bluepilot.dev/2026/06/16/bypassing-the-ford-pscm-a-first-look-at-a-ford-torque-interceptor/).

The follow-up describes intended command bounds, driver override, fault handling, and future manufacturer documentation. Those are stated design goals; the article does not provide a completed safety assessment for this Bronco. [Safety follow-up](https://bluepilot.dev/2026/06/17/a-word-on-the-safety-of-a-torque-interceptor/).

The inspected BluePilot release still defines **Bronco Sport**, with no full-size Bronco platform entry. The two vehicles must not be substituted in vehicle selection. [Pinned Ford platform definitions](https://github.com/BluePilotDev/bluepilot/blob/e1d051d7ba270261b4455068bd68f1a58db15a4a/opendbc_repo/opendbc/car/ford/values.py).

## Three approaches, with different safety implications

| Approach | What changes | Relevance to this project |
|---|---|---|
| Native lane-centering commands | An external controller supplies Ford's normal path messages. BluePilot additionally changes controller logic and Panda checks. | The interface remains a research direction. A particular fork's safety implementation requires its own assessment. |
| LKA firmware modifications | Steering firmware restrictions on repeated assistance or minimum speed are removed. | Outside the owner's retained-protection requirement. |
| Torque-sensor interceptor | Hardware alters the torque-sensor information entering the steering controller. | Does not meet an assumption that Ford's normal ADAS command limits remain the controlling boundary. |

The [LKA progress report](https://bluepilot.dev/2026/04/27/ford-lka-openpilot-progress/) points to the same firmware-research repository already used here. It is useful provenance, not an independent replication of this repository's findings.

The July angle-control work concerns steering response through native messages. It does not solve delivery across the Bronco's camera and steering network groups. [July technical article](https://bluepilot.dev/2026/07/15/bluepilot-7-0-the-return-of-angle-control-it-wasnt-the-models-fault/).

## Useful technical leads, and corrections

The [November CAN-FD control article](https://bluepilot.dev/announcements/?post=understanding-the-ford-canfd-adas-lateral-control-lane-keeping-lane-centering-bluecruise) distinguishes requested assistance from steering-controller availability and active-state feedback. It supplies useful names for a future passive-log comparison:

| Signal or message | Question to investigate |
|---|---|
| `Lane_Assist_Data3_FD1` / `LaActAvail_D_Actl` | What assistance does the steering controller report as available? |
| `LatCtlSte_D_Stat` | What assistance state does it report as active? |
| `LateralMotionControl2` | Are the expected path messages present on the relevant network? |
| `ACCDATA_3` / `Tja_D_Stat` | What companion assistance status is being communicated? |

These names are research leads from other Ford implementations. Their availability, encoding, and meaning must be checked against the Bronco's actual data. Displaying a hands-free icon does not establish steering permission or a safe operating mode.

One claim in that article needs correction: it treats the LMC2 checksum's purpose as unknown and says zero works. In the inspected current implementation, zero is a temporary packing value that is replaced with a calculated checksum before transmission. [Pinned encoder](https://github.com/BluePilotDev/bluepilot/blob/e1d051d7ba270261b4455068bd68f1a58db15a4a/opendbc_repo/opendbc/car/ford/fordcan.py). That agrees with the checksum handling independently traced in the [public Bronco comparison sample](FIRMWARE_INVESTIGATION.md#finding-3-the-checksum-matches-openpilot); it is not permission to omit the check.

The July firmware address and filter-timing claims still need an exact executable and calibration mapping. The current angle-controller code exists and holds the curvature, curvature-rate, and offset outputs at zero while using path angle, with additional processing and checks. Finding that implementation does not validate its model of the owner's steering firmware. [Pinned angle controller](https://github.com/BluePilotDev/bluepilot/blob/e1d051d7ba270261b4455068bd68f1a58db15a4a/opendbc_repo/opendbc/sunnypilot/car/ford/lateral_angle_ext.py).

## Independent safety-code check

The source snapshot inspected was:

- Release `bp-7.0`: `e1d051d7ba270261b4455068bd68f1a58db15a4a`, dated August 16, 2026.
- Development `bp-dev`: `e22afa6be9b881fa784c92ebb316db47728a3d81`, dated September 15, 2026.
- The Ford safety-header contents were identical at those two revisions.

The implementation contains custom path-angle bounds, rate checks, a separate steering-intent cross-check, and reset handling. It cannot be described simply as unchanged stock Panda safety. [Pinned safety implementation](https://github.com/BluePilotDev/bluepilot/blob/e1d051d7ba270261b4455068bd68f1a58db15a4a/opendbc_repo/opendbc/safety/modes/ford.h).

A focused host test compiled the release's unmodified C safety implementation and called its normal transmit-policy entry point with synthetic memory inputs. A control-permission rejection worked in the baseline case but was not enforced in a reset-related case. The finding reproduced with and without the debug compilation flag. This blocks recommending the inspected branch as satisfying this project's independent-safety requirement.

**Scope:** this is a software-policy result. It does not demonstrate a vehicle receiving a command, actual steering motion, defeat of Ford's internal EPS protections, or behavior of an installed device's particular firmware build. No vehicle, scanner, CAN interface, firmware flasher, or road test was involved. A complete build mapping and broader safety review remain outstanding. No issue or message was sent to another project.

## Why a connection error is not a diagnosis

Several distinct problems appear in these sources:

| Problem | What the source establishes |
|---|---|
| No ignition detection / cable faults | BluePilot documents connection problems on otherwise supported installations. These do not demonstrate a Bronco gateway solution. |
| Radar parsing errors | Older releases had a separately documented radar-data interpretation issue. |
| LKA lockout | Repeated lane-keeping requests can be rejected by steering firmware; that differs from a gateway failing to deliver a message. |
| TRON / authenticated messages | The status page concerns listed model/year combinations. Bronco Sport entries do not describe the full-size Bronco. |
| Bronco gateway delivery | Still unresolved by the material reviewed here. |

Sources: [connection troubleshooting](https://bluepilot.dev/2025/08/15/i-installed-bluepilot-but-when-i-crank-my-vehicle-nothing-happens-or-i-get-a-canbus-error-and-alerts-on-my-dash/), [radar discussion](https://bluepilot.dev/2025/08/09/on-my-canfd-ford-i-occasionally-get-radar-errors-when-using-bp-3-x-or-newer/), [loaded compatibility FAQ](https://bluepilot.dev/FAQ/), [TRON status list](https://bluepilot.dev/2025/08/13/confirmed-tron-status-list/).

## What can continue safely

1. Keep the existing firmware and source analysis offline. Use availability, active-state, and message-validation evidence to distinguish delivery from authorization.
2. Obtain the owner's matching original executable/calibration packages or a legitimate manifest identifying them. No matching gateway or steering firmware download was located in the reviewed site material or inspected source tree.
3. Treat BluePilot's bench work and firmware-analysis references as leads for locating original files and understanding behavior, with exact provenance required.
4. Independently assess every safety-critical part of any proposed controller. Neither a passing message-format check nor an encouraging bench result is sufficient.

The owner's [confirmed FORScan identifiers](FORSCAN_FINDINGS.md) remain the acquisition target. The missing gateway strategy is `MB3T-14H483-FAH`; the owner's steering strategy is `RB3C-14D003-AA`. The existing analyzed steering sample is different. No additional vehicle configuration changes are needed to continue the public-source research.

