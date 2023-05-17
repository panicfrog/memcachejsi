# react-native-memcachejsi

memcache wrapper with jsi

## Installation

iOS

```shell
pod 'MemCache-Swift'
```

Android

```shell
implemention 'com.yongping.jmemcache:MemCache:0.0.1'
```

react native

```sh
npm install react-native-memcachejsi
```

## Usage

```js
import MemCache from "react-native-memcachejsi";

// ...
// get
MemCache.getInt("<your-key-of-int>")
// put
MemCache.putInt("<your-key-for-int", 10 | 0)
// put json
MemCache.putJson('key-for-json', JSON.stringfy({key1: 'value1', key2: false}))
// patch json
MemCache.patchJson("key-for-json", JSON.stringfy({a: 10, b: 'bbb'}))
```

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT
