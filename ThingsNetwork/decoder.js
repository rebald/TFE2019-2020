function Decoder(bytes, port) {
    var value = String.fromCharCode.apply(null, bytes);
    var floatValue = parseFloat(value);
    return {
        degreesC: floatValue
    };
}