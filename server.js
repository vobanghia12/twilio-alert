import twilio from "twilio";
const accountSid = "ACfdf39a83e9561ae538d64a701d49edd6";
const authToken = "f77f333ec699b02f9ff9ecc3b686a236";
import axios from "axios";
const client = new twilio(accountSid, authToken);
const price = 5000;
const str = "+18134528015";
function numberWithCommas(x) {
  return x.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ",");
}
const fetchCoin = async () => {
  const { data } = await axios.get(
    "https://hackabull-crypto-tracker.herokuapp.com/api/user"
  );
  return data;
};

setInterval(async () => {
  const coinDatas = await fetchCoin();
  const messagePromises = coinDatas.map(coin => sendMessageForCoin(coin));
  try {
      await Promise.all(messagePromises);
  } catch (e) {
      console.log(e);
  }

}, 5000);

async function sendMessageForCoin(coin) {
  if (price <= 5000) {
    const message = await client.messages
      .create({
        // body: JSON.stringify(coin),
        // messagingServiceSid: "MGe958d53389b7e7022d9583fbd1c534e3",
        // to: str,
      });

    console.log(message);
  }
}

