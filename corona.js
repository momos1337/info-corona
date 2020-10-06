const callApi = async (host)=>{
    const data = await fetch(host,{
        headers:{
            "X-Access-Token" : "5cf9dfd5-3449-485e-b5ae-70a60e997864"
        }
    })
    try {
        return data.json()
    } catch (error) {
        console.log(error)
    }
}
const petakan = ()=>{
    callApi("https://api.covid19api.com/summary")
    .then(res=>{
        console.log(res)
        let country = "";
        res.Countries.map(i=>{
            country += '<li>'+i.Country+" Terinveksi : "+i.TotalConfirmed+" Death : "+i.TotalDeaths+" Recover : "+i.TotalRecovered+"</li><br/>";
        })
        const x = document.getElementById("slideContainer").innerHTML = country

        const Terinveksi = res.Global.TotalConfirmed
        const Recover = res.Global.TotalRecovered
        const Death = res.Global.TotalDeaths

        document.getElementById("confirm").innerHTML = Terinveksi
        document.getElementById("sembuh").innerHTML = Recover
        document.getElementById("death").innerHTML = Death
    })
}

petakan();