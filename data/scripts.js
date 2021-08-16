let url = window.location.href;
let url_host = window.location.hostname;
console.log(`url:${url}`);
console.log(`url_host:${url_host}`);

function goButton(){
    //let headers = new Headers();
    //headers.append('Access-Control-Allow-Methods: GET');
    let code_val = document.getElementById("code").value;
    let get_code_url = `${url}code?code=${code_val}`;
    console.log(`code_url:${get_code_url}`);
    
    fetch(get_code_url,
        {
            mode:   'no-cors',
            method: 'GET',
            //headers: headers
        })
        .then(response => response.json())
        .then(json => console.log(json))
        .catch(error => console.log('go button request failed!'));
}

function lampButton(){
    //let headers = new Headers();
    //headers.append('Access-Control-Allow-Methods: GET');
    let get_lamp_url = `${url}lamp?lamp=toggle`;
    console.log(`lamp_url:${get_lamp_url}`);

    fetch(get_lamp_url,
        {
            mode:   'no-cors',
            method: 'GET',
            //headers: headers
        })
        .then(response => response.json())
        .then(json => console.log(json))
        .catch(error => console.log('lamp button request failed!'));
}

function logoutButton() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "logout", true);
    xhr.send();

    setTimeout(function(){ window.open("/logged-out","_self"); }, 1000);
}

function genericButtonClick(request_url) {
    console.log(`genericButtonClick:${request_url}`);
    fetch(`${request_url}`,
        {
            mode:   'no-cors',
            method: 'GET',
            //headers: headers
        })
        .then(response => response.json()
        .then(data => {
            console.log(data.message);
            window.alert(data.message);
        })
        .catch(error => {
            var message =`Response to ${request_url} failed!`; 
            console.log(message);
            window.alert(message);
        }));
}