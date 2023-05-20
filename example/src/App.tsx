import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';
import MemCache from 'react-native-memcachejsi';

export default function App() {
  const [result, setResult] = React.useState<number | undefined>();

  React.useEffect(() => {
    // for (let v in global) {
    //   if (v == 'jsimultiply') {
    //     if (typeof global.jsimultiply == 'function') {
    //       console.log(global.jsimultiply(5, 6)) 
    //     }
    //     console.log('jsimultiply found');
    //   }
    // }

    let putInt = MemCache.putInt('intKey', 123);
    let getInt = MemCache.getInt('intKey');
    console.log(`int: \n         result: ${putInt}, getInt: ${getInt}`);

    let putDouble = MemCache.putDouble('doubleKey', 123.456);
    let getDouble = MemCache.getDouble('doubleKey');
    console.log(`double: \n         result: ${putDouble}, getDouble: ${getDouble} \n`);

    let putBoolean = MemCache.putBoolean('booleanKey', false);
    let getBoolean = MemCache.getBoolean('booleanKey');
    console.log(`boolean: \n         result: ${putBoolean}, getBoolean: ${getBoolean} \n`);

    let putStart = performance.now()
    let success = MemCache.putString('key', 'value');
    let putEnd = performance.now()
    console.log(`putString: \n         result: ${success}, performance: ${putEnd - putStart} ms`);
    let getStart = performance.now()
    let value = MemCache.getString('key');
    let getEnd = performance.now()
    console.log(`getString: \n         result: ${value}, performance: ${getEnd - getStart} ms`);

    let putJson = MemCache.putJson('jsonKey', JSON.stringify({ key: 'value' }));
    console.log(`putJson: \n         result: ${putJson}`);
    let getJson = MemCache.getJson('jsonKey');
    console.log(`getJson: \n         result: ${getJson}`);

    let modifyJson = MemCache.modifyJson('jsonKey', '$.key', 'value2');
    console.log(`modifyJson: \n         result: ${modifyJson}`);
    console.log(`getJson: \n         result: ${MemCache.getJson('jsonKey')}`);

    let patchJson = MemCache.patchJson('jsonKey', JSON.stringify({ key2: 'value2', key3: { key4: 'value3'} }));
    console.log(`patchJson: \n         result: ${patchJson}`);
    console.log(`getJson: \n         result: ${MemCache.getJson('jsonKey')}`);
    console.log(`-------------------------------------------------------------------------------`);
    setResult(MemCache.jsimultiply(9, 9));

    let putStrings = MemCache.putStrings([{ key: 'putStringskey1', value: 'value1' }, { key: 'putStringskey2', value: 'value2' }]);
    console.log(`putStrings: \n         result: ${putStrings}`);
    let putInts = MemCache.putInts([{ key: 'putIntskey1', value: 1 }, { key: 'putIntskey2', value: 2 }]);
    console.log(`putInts: \n         result: ${putInts}`);
    let putDoubles = MemCache.putDoubles([{ key: 'putDoubleskey1', value: 1.1 }, { key: 'putDoubleskey2', value: 2.2 }]);
    console.log(`putDoubles: \n         result: ${putDoubles}`);
    let putBooleans = MemCache.putBooleans([{key: 'putBooleanskey1', value: true}, {key: 'putBooleanskey2', value: false}]);
    console.log(`putBooleans: \n         result: ${putBooleans}`);
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {result}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
