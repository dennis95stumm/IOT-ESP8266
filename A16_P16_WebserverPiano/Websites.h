
//Converted with http://www.percederberg.net/tools/text_converter.html to C-String Text and saved as char

const char index[] PROGMEM = {
"<HTML><HEAD>\n<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"> \n<title>\nNanoESP Piano\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>NanoESP Piano</h1>\n<HR>\nPlay your Song:\n<br><br>\n\t<button onclick=\"return sendForm(262);\">C (4)</button>\n\t<button onclick=\"return sendForm(294);\">D (4) </button>\n\t<button onclick=\"return sendForm(330);\">E (4) </button>\n\t<button onclick=\"return sendForm(349);\">F (4) </button>\n\t<button onclick=\"return sendForm(392);\">G (4) </button>\n\t<button onclick=\"return sendForm(440);\">A (4) </button>\n\t<button onclick=\"return sendForm(494);\">B (4) </button>\n\t<button onclick=\"return sendForm(523);\">C (5) </button>\n<br>\n<HR><BR>\n<script language=\"JavaScript\">\nfunction sendForm(value) {\n  var xhr = new XMLHttpRequest();\n  xhr.open('POST', \"/dataonly\", true);\n\n  xhr.send(\"tone=\"+value);\n  return false; // Prevent page from submitting.\n}\n</script>\n\n</body>\n</HTML>\n\0"
};

const char error404[] PROGMEM = {
"<HTML><HEAD>\n<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"> \n<title>\nError\n</title>\n</HEAD>\n<BODY bgcolor=\"#FFFF99\" text=\"#000000\">\n<h1>Error 404: File or Page not found</h1>\n<HR><BR>\n<a href=\"/\">Main Page</a><br>\n<br>\n<br>\n<HR><BR>\n<img src=\"http://iot.fkainka.de/wp-content/uploads/2015/09/cropped-xBoard.png\">\n</body>\n</HTML>\0"
};


