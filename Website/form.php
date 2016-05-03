<?php
require_once "php/db_connect.php";
require_once "php/functions.php";
?>

<!DOCTYPE html>
<html>

            <!-----Bootstrap CDN---->
    <link rel="stylesheet" href="https://cdn.rawgit.com/twbs/bootstrap/v4-dev/dist/css/bootstrap.css" integrity="sha384-XXXXXXXX" crossorigin="anonymous">

    <script src="https://cdn.rawgit.com/twbs/bootstrap/v4-dev/dist/js/bootstrap.js" integrity="sha384-XXXXXXXX" crossorigin="anonymous"></script>
            <!------Bootstrap CDN------->
    
    <!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="css/bootstrap.min.css">

	<!-- Optional theme -->
	<link rel="stylesheet" href="css/bootstrap-theme.min.css">
    
    <link rel="stylesheet" href="css/styles.css">
    
<body onload="initialize();">
    
    <!------Jumbotron heading for Form----->
    <div class="row">
            <div class="form-title">
                <div class="jumbotron">
                    <h2>Schedule an Appointment with us Today!</h2>
                </div>
<form>
     
  <fieldset class="form-group"> 
    <label for="exampleInputEmail1">Full Name</label>
    <input type="email" class="form-control" id="exampleInputEmail1" placeholder="First Name followed by Last Name">
  </fieldset>
    
  <fieldset class="form-group">
    <label for="exampleInputPassword1">Device Name</label>
    <input type="password" class="form-control" id="exampleInputPassword1" placeholder="Example: Toshiba Satellite L645 Laptop">
  </fieldset>
    
  <fieldset class="form-group"> 
    <label for="exampleInputEmail1">Pick a date for your appointment. </label>
    <input type="email" class="form-control" id="exampleInputEmail1" placeholder="MM/DD/YY">
  </fieldset>
    
  <fieldset class="form-group"> 
    <label for="exampleInputEmail1">Pick a time for your appointment. </label>
    <input type="email" class="form-control" id="exampleInputEmail1" placeholder="hour:minutes AM/PM">
  </fieldset>
    
 <fieldset class="form-group">
    <label for="exampleTextarea">What is the reason for your appointment?</label>
    <textarea class="form-control" id="exampleTextarea" rows="3"></textarea>
  </fieldset>

    <div class= "button-holder">
  <button type="submit" class="btn btn-primary">Submit</button>
    </div>
</form>
 </body>
</html>
