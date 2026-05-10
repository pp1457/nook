#pragma once

#include <ctime>
#include <format>

inline std::string greeting(std::tm tm) {
  int hour = tm.tm_hour;
  if (hour < 5)   return "still up · ";
  if (hour < 12)  return "good morning · ";
  if (hour < 19)  return "good afternoon · ";
  if (hour < 23)  return "good evening · ";
  return "late night · ";
}

inline std::string display_date(std::tm tm) {

  const char* day_names[] = {
    "Sun", "Mon", "Tue", "Wed",
    "Thu", "Fri", "Sat"
  };

  const char* month_names[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  return std::format("{} · {} {}",
      day_names[tm.tm_wday], 
      month_names[tm.tm_mon], 
      tm.tm_mday
  ); 
}

