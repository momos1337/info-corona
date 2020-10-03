import requests,json,os
os.system('clear')

print("coded by 4LM05TH3V!L ft BinsarDJ\n")
print("Greetz: Hidden Ghost Team ~ IndoSec ~ Sorong6etar\n\n")
print("Country   : Indonesia    \n")

req = requests.get('https://covid19.mathdro.id/api')
data = json.loads(req.text)


print(f"Positif   : {data['confirmed']['value']:,}")
print(f"Sembuh    : {data['recovered']['value']:,}")
print(f"Meninggal : {data['deaths']['value']:,}")