import { NativeModules, Platform } from 'react-native';

declare interface Global {
  memcachejsi: {
    jsimultiply: (a: number, b: number) => number;
    getString: (key: string) => string | undefined;
    getInt: (key: string) => number | undefined;
    getDouble: (key: string) => number | undefined;
    getBoolean: (key: string) => boolean | undefined;
    putString: (key: string, value: string) => boolean;
    putInt: (key: string, value: number) => boolean;
    putDouble: (key: string, value: number) => boolean;
    putBoolean: (key: string, value: boolean) => boolean;
    putStrings: (pairs: Array<{key: string, value: string}>) => boolean;
    putInts: (pairs: Array<{key: string, value: number}>) => boolean;
    putDoubles: (pairs: Array<{key: string, value: number}>) => boolean;
    putBooleans: (pairs: Array<{key: string, value: boolean}>) => boolean;
    getJson: (key: string) => string | undefined;
    putJson: (key: string, value: string) => boolean;
    modifyJson: (key: string, path: string, value: string) => boolean;
    patchJson: (key: string, value: string) => boolean;
  }
  
}
declare const global: Global;

const LINKING_ERROR =
  `The package 'react-native-memcachejsi' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

const Memcachejsi = NativeModules.Memcachejsi
  ? NativeModules.Memcachejsi
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export function multiply(a: number, b: number): Promise<number> {
  return Memcachejsi.multiply(a, b);
}

const memcachejsi = global.memcachejsi

export default memcachejsi;