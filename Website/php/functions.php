<?php
    require 'db_connect.php';
    $connection = new mysqli($dbhost, $dbuser, $dbpass, $dbname);
    function sanitizeString($_db, $str)
    {
        $str = strip_tags($str);
        $str = htmlentities($str);
        $str = stripslashes($str);
        return mysqli_real_escape_string($_db, $str);
    }
    function SavePostToDB($_db, $_device, $_date, $_time, $_reason)
    {
        echo "Saving to DB";
    	/* Prepared statement, stage 1: prepare query */
    	if (!($stmt = $_db->prepare("INSERT INTO Apppointment(device, appt_date, appt_time, reason) VALUES (?, ?, ?, ?)")))
    	{
	    	echo "Prepare failed: (" . $_db->errno . ") " . $_db->error;
    	}

	    /* Prepared statement, stage 2: bind parameters*/
    	if (!$stmt->bind_param('ssss', $_device, $_date, $_time, $_reason))
    	{
    		echo "Binding parameters failed: (" . $stmt->errno . ") " . $stmt->error;
	    }

    	/* Prepared statement, stage 3: execute*/
    	if (!$stmt->execute())
    	{
    		echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
    	}
     
    }

    function getContent($_db, $user)
    {
        $query = "SELECT USER_USERNAME, STATUS_TITLE, STATUS_TEXT, TIME_STAMP, IMAGE_NAME, FILTER, COMMENT_ID FROM WALLI ORDER BY TIME_STAMP DESC";
        if(!$result = $_db->query($query))
        {
            die('There was an error running the query [' . $_db->error . ']');
        }
        $output = '';
        $count = 0;
        while($row = $result->fetch_assoc())
        {
            $title = $row['STATUS_TITLE'];
            $text = $row['STATUS_TEXT'];
            $time = getRelTime($row['TIME_STAMP']);
            
            $output = $output . '<div class="row"><div class="col-md-7"><img class="img-responsive center-block" src="' 
            . 'quarantine/' . $row['IMAGE_NAME'] . '" width="450px" style="-webkit-filter:'
            . $row['FILTER'] . '"></div><div class="col-md-5"><h3>'
            . unescapeSpecialCharacters($title) . '</h3>'
            . '<h4>Posted by <strong>' . $row['USER_USERNAME'] . '</strong> ' . $time . '</h4>'
            . "<p>" . unescapeSpecialCharacters($text) . "</p>" 
            . '<form name="View Comments" action="./comments.php" method="GET">'
            . '<input type="hidden" name="post" value=' . hash('ripemd128', $row['TIME_STAMP'] . $row['USER_USERNAME']) . ">"
            . '<input class="btn btn-primary btn-xs" type="submit" value="View Comments >>">'
            . '</form>';
                
            if ($user == 'Lilian' || $user == 'omarques')
            {
                $output = $output . '<br><form name="Remove Post ' . $count
                . '" class="form-horizontal" method="POST" action="./php/remove_post.php">'
                . '<input type="button" value="Remove Post ' . $count
                . '" class="btn btn-danger btn-xs" id="remove_post">'
                . '<input type="hidden" class="form-control" name="image_name" value="' 
                . $row['IMAGE_NAME'] . '" id="image_name">'
                . '</form>' ;
            }
            
            $output = $output . '</div></div><hr>' ;
            $count = $count + 1;
        }
        
        return $output;
    }
    function destroySession()
    {
        $_SESSION=array();
        if (session_id() != "" || isset($_COOKIE[session_name()]))
            setcookie(session_name(), '', time()-3200000, '/');
        session_destroy();
    }
     function encrypt($str)
     {
         $salt1 = "3*2^7";
         $salt2 = "#>*w1";
         return hash('ripemd128', "$salt1$str$salt2");
     }
     function queryMysql($query)
     {
         global $connection;
         $result = $connection->query($query);
         if (!$result) die($connection->error);
         return $result;
     }
    
    function getRelTime($time){
        $diff = time() - $time;
        
        $day_diff = floor($diff / 86400);
        if($day_diff == 0)
        {
            if($diff < 60) return 'just now';
            if($diff < 120) return '1 minute ago';
            if($diff < 3600) return floor($diff / 60) . ' minutes ago';
            if($diff < 7200) return '1 hour ago';
            if($diff < 86400) return floor($diff / 3600) . ' hours ago';
        }
        if($day_diff == 1) return 'yesterday';
        if($day_diff < 7) return $day_diff . ' days ago';
        if($day_diff == 7) return '1 week ago';
        if($day_diff < 31) return ceil($day_diff / 7) . ' weeks ago';
        if($day_diff < 60) return 'last month';
        return date('F Y', $time);
    }
    function unescapeSpecialCharacters($str)
    {
        $str = str_replace("\'", "'", "$str");
        $str = str_replace('\"', '"', "$str");
        $str = str_replace("\;", ";", "$str");
        $str = str_replace("\:", ":", "$str");
        $str = str_replace("\/", "/", "$str");
        
        return $str;
    }
?>
