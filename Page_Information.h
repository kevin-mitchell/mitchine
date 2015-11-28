#ifndef PAGE_INFOMATION_H
#define PAGE_INFOMATION_H


//
//   The HTML PAGE
//
const char PAGE_Information[] PROGMEM = R"=====(
	<!doctype html>
<meta name="viewport" content="width=device-width, initial-scale=1" />
<script>function microAjax(B,A){this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};this.stateChange=function(D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};this.postBody=(arguments[2]||"");this.callbackFunction=A;this.url=B;this.request=this.getRequest();if(this.request){var C=this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}C.send(this.postBody)}};

function setValues(url)
{
	microAjax(url, function (res)
	{
		res.split(String.fromCharCode(10)).forEach(function(entry) {
		fields = entry.split("|");
		if(fields[2] == "input")
		{
				document.getElementById(fields[0]).value = fields[1];
		}
		else if(fields[2] == "div")
		{
				document.getElementById(fields[0]).innerHTML  = fields[1];
		}
		else if(fields[2] == "chk")
		{
				document.getElementById(fields[0]).checked  = fields[1];
		}
	  });
	});
}</script> 
<html>
	<head>
	<title></title>
	<meta charset="utf-8" />
	<style>.btn,.btn:link,.btn:visited,body{font-family:avenir,helvetica,arial,sans-serif;letter-spacing:.15em}body{color:#000}hr{background-color:#eee;border:0;color:#eee;height:1px}.btn,.btn:link,.btn:visited{border-radius:.3em;border-style:solid;border-width:1px;color:#111;display:inline-block;margin-bottom:.5em;padding:1em .75em;text-decoration:none;text-transform:uppercase;-webkit-transition:color .4s,background-color .4s,border .4s;transition:color .4s,background-color .4s,border .4s}.btn:focus,.btn:hover{color:#7FDBFF;border:1px solid #7FDBFF;-webkit-transition:background-color .3s,color .3s,border .3s;transition:background-color .3s,color .3s,border .3s}.btn:active{color:#0074D9;border:1px solid #0074D9;-webkit-transition:background-color .3s,color .3s,border .3s;transition:background-color .3s,color .3s,border .3s}.btn--s{font-size:12px}.btn--m{font-size:14px}.btn--l{font-size:20px;border-radius:.25em!important}.btn--full,.btn--full:link{border-radius:.25em;display:block;margin-left:auto;margin-right:auto;text-align:center;width:100%}.btn--blue:link,.btn--blue:visited{color:#fff;background-color:#0074D9}.btn--blue:focus,.btn--blue:hover{color:#fff!important;background-color:#0063aa;border-color:#0063aa}.btn--blue:active{color:#fff;background-color:#001F3F;border-color:#001F3F}@media screen and (min-width:32em){.btn--full{max-width:16em!important}}
	</style>
	<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	</head>
	<body>
<h1 style="font-family:Helvetica Neue, Helvetica, Arial, SANS-SERIF;font-size:3em; margin:.5em;font-weight:100;">Mitchine</h1>
<a href="admin.html"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Network Information</strong>
<hr>
<table border="0"  cellspacing="0" cellpadding="3" style="width:310px" >
<tr><td align="right">SSID :</td><td><span id="x_ssid"></span></td></tr>
<tr><td align="right">IP :</td><td><span id="x_ip"></span></td></tr>
<tr><td align="right">Netmask :</td><td><span id="x_netmask"></span></td></tr>
<tr><td align="right">Gateway :</td><td><span id="x_gateway"></span></td></tr>
<tr><td align="right">Mac :</td><td><span id="x_mac"></span></td></tr>

<tr><td colspan="2"><hr></span></td></tr>


<tr><td colspan="2" align="center"><a href="javascript:GetState()" class="btn btn--m btn--blue">Refresh</a></td></tr>
</table>
<script>

function GetState()
{
	setValues("/admin/infovalues");
}

window.onload = function ()
{
	GetState();
}




</script>
</body>
</html>
)=====" ;


//
// FILL WITH INFOMATION
// 

void send_information_values_html ()
{

	String values ="";

	values += "x_ssid|" + (String)WiFi.SSID() +  "|div\n";
	values += "x_ip|" +  (String) WiFi.localIP()[0] + "." +  (String) WiFi.localIP()[1] + "." +  (String) WiFi.localIP()[2] + "." + (String) WiFi.localIP()[3] +  "|div\n";
	values += "x_gateway|" +  (String) WiFi.gatewayIP()[0] + "." +  (String) WiFi.gatewayIP()[1] + "." +  (String) WiFi.gatewayIP()[2] + "." + (String) WiFi.gatewayIP()[3] +  "|div\n";
	values += "x_netmask|" +  (String) WiFi.subnetMask()[0] + "." +  (String) WiFi.subnetMask()[1] + "." +  (String) WiFi.subnetMask()[2] + "." + (String) WiFi.subnetMask()[3] +  "|div\n";
	values += "x_mac|" + GetMacAddress() +  "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 

}


#endif
