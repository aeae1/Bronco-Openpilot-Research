# What the research means

The central question is whether openpilot can send ordinary Ford lane-centering requests that the Bronco's existing steering system will accept, while that system continues enforcing its normal protections.

Three things have to work separately:

1. **Delivery:** the request must reach the steering computer. The camera and steering computer can sit on different network segments, with a gateway between them.
2. **Understanding and permission:** the steering computer must recognize the request, judge it fresh and valid, and allow lane centering in the current vehicle state.
3. **Safe control:** both the steering computer and Panda must enforce appropriate limits and disengagement behavior. Getting a wheel to move would establish much less than this.

## What we actually learned

The public firmware has more than a label for the newer lane-centering message, called **LMC2**. We followed how that message is looked up, handed between internal software layers, recorded as received, and checked by the application.

We corrected one detail in a public table description. Its grouping of the bytes pointed LMC2 toward the internal number for the neighboring message. Following the instructions that read the table identifies the correct internal number, 23. This gives subsequent analysis a firmer starting point. It does not prove that the table mistake caused anybody's vehicle experiment to fail.

We also checked the message's checksum calculation. A checksum is a small arithmetic check on a message's contents. A counter helps distinguish successive messages, while timeout handling detects missing or stale information. The firmware's checksum arithmetic matched upstream openpilot's Ford calculation in all 10,640 offline comparisons. That means this one part of the message format agrees; it does not mean the steering computer has agreed to steer.

The firmware includes freshness and error handling. The goal is to understand and satisfy those checks during legitimate operation. We have not established that a special keep-alive is the missing ingredient, and we have not proved a particular timeout is the original problem.

Finally, we identified default calibration fields used by the validation logic. Their physical timing units and the runtime selection of those defaults remain unresolved. No values were changed.

The [technical report](FIRMWARE_INVESTIGATION.md) contains the addresses, source links, method, and limits behind these statements.

## How this compares with previous attempts

| Earlier public work | What it established or reported | How this investigation relates |
|---|---|---|
| AJ/BluePilot development discussion | A legacy-CAN camera, CAN-FD steering rack, and gateway delivery problems were reported. Direct-rack harness work encountered network-termination problems. | Our firmware work does not fix the wiring or prove delivery. It identifies what to inspect after delivery is established. |
| ghostdev137's firmware repository | Published the firmware sample, tables, calibration observations, and reverse-engineering work. | We relied on that sample, corrected a table interpretation, and followed the receiver further into validation. |
| The inspected mims002 experimental fork | Uses the older lane-assistance path and changes part of the independent safety policy; it also enables openpilot longitudinal control for the Bronco profile. | It is not evidence that the native LMC2 approach works with the project's intended protections and factory ACC behavior. |
| The 2024 demonstration video | Documents the existence of an earlier test build. | Playback was not examined during this investigation. The video was not treated as proof of sustained, validated operation. |

The delivery and harness reports are [firsthand posts in the Bronco6G development thread](https://www.bronco6g.com/forum/threads/enabling-intelligent-adaptive-cruise-control-and-lane-centering.71121/page-29). Source revisions and fork-specific findings are documented in the [technical report](FIRMWARE_INVESTIGATION.md).

There is no basis to say previous developers lacked the ability to find this. Some had already decompiled steering firmware. The contribution here is a documented, reproducible set of narrower findings. Private discussion may contain additional progress.

## Is there reason for hope?

Yes, there is a specific technical reason to keep investigating: the public sample contains a recognizable factory receive and validation path. That is more encouraging than finding no such path.

The difficult part is still unresolved. We need to match the installed firmware, establish delivery, and trace all conditions between receiving the request and permitting steering. A legitimate configuration could be missing, a path could be inactive in this vehicle, or additional limits could make the intended use impractical. Current evidence cannot choose between those outcomes.

The [next-step plan](NEXT_STEPS.md) is designed to resolve those questions one at a time.
