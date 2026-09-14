# language=V850:LE:32:v850e3v5
ram:000f39ec  80072100  prepare { lp },0x0
ram:000f39f0  80ff4404  jarl 0x000f3e34,lp
ram:000f39f4  80ff3a03  jarl 0x000f3d2e,lp
ram:000f39f8  80ffb40b  jarl 0x000f45ac,lp
ram:000f39fc  40063f00  dispose 0x0,{ lp },[lp]
