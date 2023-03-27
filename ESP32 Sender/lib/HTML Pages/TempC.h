#define TempC_h
#ifdef TempC_h
#include "Arduino.h"

const char tempC_html[] PROGMEM = R"CelsiusRawString(
  <!DOCTYPE HTML><html>
  <head>
    <title>ESP32 Celsius Page</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
  </head>
  <style>
    body { margin: 0; background-color: lightgray; }

    ul.topnav {
      list-style-type: none;
      margin: 0;
      padding: 0;
      overflow: hidden;
      background-color: #333;
    }

    ul.topnav li {float: none;}

    ul.topnav li a {
      display: block;
      color: white;
      text-align: center;
      padding: 14px 16px;
      text-decoration: none;
    }

    ul.topnav li a:hover:not(.active) {background-color: #111;}

    ul.topnav li a.active {background-color: orange;}
  </style>
  <body>
    <ul class="topnav">
      <li><a href="/">HOME</a></li>
      <li><a class="active" href="CelsiusPage">Temperature C</a></li>
      <li><a href="FahrPage">Temperature F</a></li>
      <li><a href="HumiPage">Humidity</a></li>
    </ul>
    <h3>Temperature: %TEMPCPLACEHOLDER% &#8451</h3>
  </body>
  </html>
)CelsiusRawString";

#endif