import { NativeModules, Platform } from 'react-native';
const LINKING_ERROR = `The package 'react-native-memcachejsi' doesn't seem to be linked. Make sure: \n\n` + Platform.select({
  ios: "- You have run 'pod install'\n",
  default: ''
}) + '- You rebuilt the app after installing the package\n' + '- You are not using Expo managed workflow\n';
const Memcachejsi = NativeModules.Memcachejsi ? NativeModules.Memcachejsi : new Proxy({}, {
  get() {
    throw new Error(LINKING_ERROR);
  }
});
export function multiply(a, b) {
  return Memcachejsi.multiply(a, b);
}
export function jsimultiply(a, b) {
  return global.jsimultiply(a, b);
}
//# sourceMappingURL=index.js.map