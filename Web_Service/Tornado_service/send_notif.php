<?php
// API access key from Google API's Console
// include 'database_handler.php';


// if($_SERVER['REQUEST_METHOD'] == 'POST'){
if(isset($send)){
	// $token_tujuan = $_POST['token_tujuan'];
	// $title = $_POST['token_tujuan'];

	$title = "Note :";
	$body =$_POST['note'];
// if(true){
	
	// $query = mysqli_query($con,$sql);
	
	// print_r($query);
	$result = array();
	// $hasil = mysqli_fetch_all($query);
	foreach ($query as $key => $value) {
		# code...
		// print_r($key);
		// print_r($value);
		$result[]= $value['token'];
	}
	$token_tujuan =$result;

		define('API_ACCESS_KEY','AAAAFawvTf8:APA91bFHNepdyK2XhXBDM4D_5s8fQ3kA8TFFd2nvh2FuCmgIE3sDyW0UzEpQIrHr0VFxE2N9SKQqsEIj9JvYlDgNOQAr7KVuNkpCPh1QhVhySfqX0dlHVGr3Oi1QOaSDbnqLX49FlhmFpnhYkQH_kUl1SQMUseuHVg');
		$url = 'https://fcm.googleapis.com/fcm/send';
		//$registrationIds = array($_GET['id']);
		$registrationIds =$token_tujuan;
		// prepare the message
		$message = array( 
		  'title'     => $title,
		  'body'      => $body
		);
		$fields = array( 
		  'registration_ids' => $registrationIds, 
		  // 'data'             => $message  --> Wrong written
		  'data'             => $message
		);
		$headers = array( 
		  'Authorization: key='.API_ACCESS_KEY, 
		  'Content-Type: application/json'
		);
		$ch = curl_init();
		curl_setopt( $ch,CURLOPT_URL,$url);
		curl_setopt( $ch,CURLOPT_POST,true);
		curl_setopt( $ch,CURLOPT_HTTPHEADER,$headers);
		curl_setopt( $ch,CURLOPT_RETURNTRANSFER,true);
		curl_setopt( $ch,CURLOPT_SSL_VERIFYPEER,false);
		curl_setopt( $ch,CURLOPT_POSTFIELDS,json_encode($fields));
		$result = curl_exec($ch);
		curl_close($ch);

		$respon['Pesan'] = "Good ".$con->error;
		$respon['id_arduino'] = 1;
		echo json_encode($respon);
		
		// echo $result;
	}
	else{

		$respon["status"] = "ok";
		$respon["json_api_version"]="0.0.1";
		echo json_encode($respon);
	}
?>	