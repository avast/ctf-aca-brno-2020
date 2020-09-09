<?php
session_start();

$errorMsg = "";

$validUser = $_SESSION["login"] === true;
if(isset($_POST["username"]) && isset($_POST["password"])) {
  $validUser = $_POST["username"] == "loudRos355" && $_POST["password"] == "mixopura82";
  if(!$validUser)
	  $errorMsg = "Invalid username or password.";
  else
	  $_SESSION["login"] = true;
}
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" />
    <link rel="stylesheet" href="css.css" />

    <title>Completely legit site! Trust me!</title>
  </head>
  <body>
    <div class="row">
      <div class="col-xs-12 col-sm-9 col-md-6 col-xl-4 mx-auto text-center">
        <?php if($validUser): ?>
          <p>avastCTF{My_buffers_are_bleeding!}</p>
        <?php else: ?>
          <form class="form-signin" method="POST" action="/">
            <img class="mb-4" src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/dc/Heartbleed.svg/501px-Heartbleed.svg.png"" width="72" />
            <h1 class="h3 mb-3 font-weight-normal">Please sign in</h1>
            <input type="text" name="username" class="form-control" placeholder="username" required autofocus />
            <input type="password" name="password" class="form-control" placeholder="Password" required />
            <div class="mb-3 text-danger"><?= $errorMsg ?></div>
            <button class="btn btn-lg btn-primary btn-block" type="submit">
              Sign in
            </button>
          </form>
        <?php endif; ?>
      </div>
    </div>
  </body>
</html>
