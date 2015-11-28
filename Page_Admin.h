

//
//  HTML PAGE
//

const char PAGE_AdminMainPage[] PROGMEM = R"=====(
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
	<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title></title>
	<meta charset="utf-8" />
	<style>.btn,.btn:link,.btn:visited,body{font-family:avenir,helvetica,arial,sans-serif;letter-spacing:.15em}body{color:#000}hr{background-color:#eee;border:0;color:#eee;height:1px}.btn,.btn:link,.btn:visited{border-radius:.3em;border-style:solid;border-width:1px;color:#111;display:inline-block;margin-bottom:.5em;padding:1em .75em;text-decoration:none;text-transform:uppercase;-webkit-transition:color .4s,background-color .4s,border .4s;transition:color .4s,background-color .4s,border .4s}.btn:focus,.btn:hover{color:#7FDBFF;border:1px solid #7FDBFF;-webkit-transition:background-color .3s,color .3s,border .3s;transition:background-color .3s,color .3s,border .3s}.btn:active{color:#0074D9;border:1px solid #0074D9;-webkit-transition:background-color .3s,color .3s,border .3s;transition:background-color .3s,color .3s,border .3s}.btn--s{font-size:12px}.btn--m{font-size:14px}.btn--l{font-size:20px;border-radius:.25em!important}.btn--full,.btn--full:link{border-radius:.25em;display:block;margin-left:auto;margin-right:auto;text-align:center;width:100%}.btn--blue:link,.btn--blue:visited{color:#fff;background-color:#0074D9}.btn--blue:focus,.btn--blue:hover{color:#fff!important;background-color:#0063aa;border-color:#0063aa}.btn--blue:active{color:#fff;background-color:#001F3F;border-color:#001F3F}@media screen and (min-width:32em){.btn--full{max-width:16em!important}}
	</style>
	</head>
	<body>
  <h1 style="font-family:Helvetica Neue, Helvetica, Arial, SANS-SERIF;font-size:3em; margin:.5em;font-weight:100;">Mitchine</h1>
<strong>Administration</strong>
<hr>
<a href="config.html" style="width:250px" class="btn btn--m btn--blue" >Network Configuration</a><br>
<a href="info.html"   style="width:250px"  class="btn btn--m btn--blue" >Network Information</a><br>


<script>


</script>

)=====";


