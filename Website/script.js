document.addEventListener("DOMContentLoaded", function() {
    function generateRandomNumber(min, max) {
        return Math.random() * (max - min) + min;
    }

    function updateEnvironmentParametersDisplay() {
        var temperatureElement = document.getElementById("temperature");
        var co2Element = document.getElementById("co2");
        var humidityElement = document.getElementById("humidity");
        var calibrateElement = document.getElementById("calibrate");
        var o3Element = document.getElementById("o3");
        var methaneElement = document.getElementById("methane");
        var alcoholElement = document.getElementById("alcohol");
        var propaneElement = document.getElementById("propane");
        var aqiElement = document.getElementById("aqi");

        var temperature = Math.floor(generateRandomNumber(25, 27));
        var co2Level = 421;
        var humidity = Math.floor(generateRandomNumber(64, 68));
        var calibrate = Math.random() < 0.5 ? "True" : "False";
        var o3PPM = generateRandomNumber(77409240, 83561712).toFixed(2);
        var methane = generateRandomNumber(-42.15, -40.47).toFixed(2);
        var alcohol = generateRandomNumber(-59.90, -60.26).toFixed(2);
        var propane = generateRandomNumber(-80.55, -82.21).toFixed(2);
        var aqi = 20;
        var aqiStatus = "Good air";

        temperatureElement.textContent = "Temperature: " + temperature + "°C";
        co2Element.textContent = "CO2 Level: " + co2Level + " ppm";
        humidityElement.textContent = "Humidity: " + humidity + "%";
        calibrateElement.textContent = "Calibrate Environment Data: " + calibrate;
        o3Element.textContent = "O3 PPM: " + o3PPM;
        methaneElement.textContent = "Methane: " + methane;
        alcoholElement.textContent = "Alcohol: " + alcohol;
        propaneElement.textContent = "Propane: " + propane;
        aqiElement.textContent = "Air Quality Index (AQI): " + aqi.toFixed(2) + "\n" + aqiStatus;

        if (aqi <= 50) {
            aqiElement.style.color = "green";
        } else if (aqi <= 100) {
            aqiElement.style.color = "yellow";
        } else if (aqi <= 150) {
            aqiElement.style.color = "orange";
        } else if (aqi <= 200) {
            aqiElement.style.color = "red";
        } else {
            aqiElement.style.color = "purple";
        }
    }

    updateEnvironmentParametersDisplay();

    setInterval(updateEnvironmentParametersDisplay, 10000);
});
