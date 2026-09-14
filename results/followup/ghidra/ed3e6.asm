# language=V850:LE:32:v850e3v5
ram:000ed3e6  80072100  prepare { lp },0x0
ram:000ed3ea  80ff3600  jarl 0x000ed420,lp
ram:000ed3ee  80ff9604  jarl 0x000ed884,lp
ram:000ed3f2  80ff7002  jarl 0x000ed662,lp
ram:000ed3f6  40063f00  dispose 0x0,{ lp },[lp]
