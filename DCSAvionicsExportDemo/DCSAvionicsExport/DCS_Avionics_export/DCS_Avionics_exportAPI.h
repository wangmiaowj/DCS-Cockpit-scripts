#pragma once

#ifdef DCSAVIONICSEXPORT_EXPORTS
#define DCS_AVIONICS_EXPORT_API __declspec(dllexport)
#else
#define DCS_AVIONICS_EXPORT_API __declspec(dllimport)
#endif
