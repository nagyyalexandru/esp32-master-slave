#define Index_h
#ifdef Index_h
#include "Arduino.h"

const char index_html[] PROGMEM = R"IndexRawString(
  <!DOCTYPE HTML><html>
  <head>
    <title>ESP32 Index</title>
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

    ul.topnav li a.active {background-color: #7BA6B4;}

    ul.topnav li.right {float: none;}
  </style>
  <body>
    <ul class="topnav">
      <li><a class="active" href="/">HOME</a></li>
      <li><a href="CelsiusPage">Temperature C</a></li>
      <li><a href="FahrPage">Temperature F</a></li>
      <li><a href="HumiPage">Humidity</a></li>
    </ul>
  </body>
  </html>
)IndexRawString";

#endif