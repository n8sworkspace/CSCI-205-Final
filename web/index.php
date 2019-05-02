<!--
This code contains contains both the rendered user side html and server side php.
When a browser hits the /website folder it renders the index.php html code to the 
browser.
-->
<html>
<body>

<div class="menu">
<?php include 'menu.php';?>
</div>
</body>
</html>

<html>
    <head>
    </head>
    <body style="margin:0px;">
        <div style="margin: 20px; border: solid 20px;background: white;">
      <p style="margin:10">
        
        <div class='container'><p> </p>
        <form  action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post">
        <fieldset class="form-group">
        <legend>Control that pi...</legend>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="GPIOcontrol" id="optionsRadios1" value="s" checked>
                Check status of the light
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="GPIOcontrol" id="optionsRadios2" value="o">
                Turn on the light
                </label>
            </div>
            <div class="form-check disabled">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="GPIOcontrol" id="optionsRadios3" value="f">
                Turn off the light
                </label>
            </div>
            <div class="form-check disabled">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="GPIOcontrol" id="optionsRadios3" value="b">
                Blink the light
                </label>
            </div>
            <div class="form-check disabled">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="GPIOcontrol" id="optionsRadios3" value="t">
                Check the Temperature
                </label>
            </div>
        </fieldset>
        <button type="submit" class="btn btn-primary">Submit</button>
        </form>
        </div>
        </p>
    </div>
    </body>

</html>

<?php
/**************************************
  Server Side php scripting
  Re-posts back to same page
****************************************/ 
    $input = "";
    $output = "";

  if ($_SERVER["REQUEST_METHOD"] == "POST"){
	$input = "/usr/lib/cgi-bin/blinky"." ".$_POST["GPIOcontrol"];
    //echo $input."<br>";
    exec($input, $output);
    if ($_POST["GPIOcontrol"]=="s")
	   echo "<div class='container'>".$output[0]."</div>";
	if ($_POST["GPIOcontrol"]=="o")
	   echo "<div class='container'>Turn Light On<br></div>";
    if ($_POST["GPIOcontrol"]=="f")
	   echo "<div class='container'>Turn Light Off<br></div>";
    if ($_POST["GPIOcontrol"]=="t")
	   echo "<div class='container'>".$output[0]."</div>";
	if ($_POST["GPIOcontrol"]=="b"){
        echo "<div class='container'>Light Blinked 2 Times<br></div>";
	  
       	 
         
	}
  }
?>
