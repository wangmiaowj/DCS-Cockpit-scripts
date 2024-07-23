dofile(LockOn_Options.common_script_path..'Radio.lua')

local gettext = require("i_18n")
_ = gettext.translate

-- —опоставление частот Localizer & Glideslope
-- The ILS operates between 108.1 and 111.95 MHz and has 40 possible channels selected from the ILS control panel

-- a note for future implementation:
-- VOR min field strength - 90 uV/m (39dB(uV/m))

-- Per ANV-141 specification:
-- VOR/LOC Ц 3 uV emf for flag out of view; VOR/LOC Ц Aural 3 uV for 6dB ((S + N)/N)
innerNoise = getInnerNoise(3.0E-6, 6) -- ((S + N)/N)
-- Minimun localizer field strength is 32 dB(uV/m) (40 uV/m) per ICAO specification.
-- Minimum reception zone per ICAO is - 25 nm for narrow area, and 17 nm for wide area.
-- Currently localizer can be received around 75 nm in narrow area, and around 25 nm in wide area.
-- NOTE: V/m may be incorrect - should be V
localizerMinSignal = 1.0E-4 -- V/m
glideslopeMinSignal = 1.5E-3 -- V/m
markerMinSignal = 1.1E-3; -- V/m

ILS_FAILURE_TOTAL			= 0
ILS_FAILURE_ANT_LOCALIZER	= 1
ILS_FAILURE_ANT_GLIDESLOPE	= 2
ILS_FAILURE_ANT_MARKER		= 3

Damage = {	{Failure = ILS_FAILURE_TOTAL, Failure_name = "ILS_FAILURE_TOTAL", Failure_editor_name = _("ILS total failure"),  Element = 7, Integrity_Treshold = 0.25, work_time_to_fail_probability = 0.5, work_time_to_fail = 3600*300},
		{Failure = ILS_FAILURE_ANT_LOCALIZER, Failure_name = "ILS_FAILURE_ANT_LOCALIZER", Failure_editor_name = _("ILS localizer antenna"),  Element = 36, Integrity_Treshold = 0.1, work_time_to_fail_probability = 0.5, work_time_to_fail = 3600*300},
		{Failure = ILS_FAILURE_ANT_GLIDESLOPE, Failure_name = "ILS_FAILURE_ANT_GLIDESLOPE", Failure_editor_name = _("ILS glideslope antenna"),  Element = 36, Integrity_Treshold = 0.2, work_time_to_fail_probability = 0.5, work_time_to_fail = 3600*300},
		{Failure = ILS_FAILURE_ANT_MARKER, Failure_name = "ILS_FAILURE_ANT_MARKER", Failure_editor_name = _("ILS marker antenna"),  Element = 7, Integrity_Treshold = 0.75, work_time_to_fail_probability = 0.5, work_time_to_fail = 3600*300}}
