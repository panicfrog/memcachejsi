"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.jsimultiply = jsimultiply;
exports.multiply = multiply;
var _reactNative = require("react-native");
const LINKING_ERROR = `The package 'react-native-memcachejsi' doesn't seem to be linked. Make sure: \n\n` + _reactNative.Platform.select({
  ios: "- You have run 'pod install'\n",
  default: ''
}) + '- You rebuilt the app after installing the package\n' + '- You are not using Expo managed workflow\n';
const Memcachejsi = _reactNative.NativeModules.Memcachejsi ? _reactNative.NativeModules.Memcachejsi : new Proxy({}, {
  get() {
    throw new Error(LINKING_ERROR);
  }
});
function multiply(a, b) {
  return Memcachejsi.multiply(a, b);
}
function jsimultiply(a, b) {
  return global.jsimultiply(a, b);
}
//# sourceMappingURL=index.js.map