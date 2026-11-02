This Flipper application reads data from automotive tire pressure sensors (TPMS), showing information on the pressure, tire temperature etc. It supports multiple manufacturer's protocols used across different car brands (Opel, Ford, Toyota, PSA/FCA, Renault/Nissan). The data can be saved, as well as modified and resent.

Apart from reading RF data (Radio Frequency, which for TPMS sensors is usually 433.92 MHz or 315 MHz), it can also be used to "wake up" (trigger) some sensors using LF (Low Frequency) signals on 125 kHz (which is used e.g. during the "relearn" process) to send the RF transmission. This covers (but is not limiting to) job done by tools like EL-50448 (multiple brands) and EL-50449 (mainly Ford). in the TPMS Editor, the EL-50449 mode is additionally able to trigger some VDO sensors used in FCA cars (which is not possible with the EL-50449 tool itself).

Below a video showing reading, editing and resending data (with a Polish version of the app, the source here is in English):

[![Flipper Zero TPMS Editor](https://img.youtube.com/vi/aIcpu-JTDtM/0.jpg)](https://www.youtube.com/watch?v=aIcpu-JTDtM)

The code is mostly altruista86's work, based on TPMS Reader (by wosk) and with ProtoView (by antirez) core. Currently maintained here (by TxF).
