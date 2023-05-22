#include "react-native-memcachejsi.h"
#include "MemCach_Cpp.hpp"

namespace memcachejsi {
using namespace facebook::jsi;

int multiply(double a, double b) {
  return a * b;
}

// This is the function that will be exposed to JS
void setup_jsimultiply(facebook::jsi::Runtime& jsiRuntime,
                       facebook::jsi::Object& obj,
                       const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    if (count != 2) {
      throw std::invalid_argument("multiply expects exactly 2 arguments");
    }
    if (!arguments[0].isNumber() || !arguments[1].isNumber()) {
      throw std::invalid_argument("multiply expects exactly 2 numbers");
    }
    double a = arguments[0].asNumber();
    double b = arguments[1].asNumber();
    return multiply(a, b);
  };
  auto jsimutilply = Function::createFromHostFunction(jsiRuntime,
                                                      PropNameID::forAscii(jsiRuntime, name),
                                                      2,
                                                      impl);
  obj.setProperty(jsiRuntime, name, std::move(jsimutilply));
}

using namespace memcache;

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

// 获取key
#define GET_KEY(count, arguments, runtime, key, funcName) \
if (count != 1) { \
throw std::invalid_argument(STRINGIZE(funcName)" : expects exactly 1 argument"); \
} \
if (!arguments[0].isString()) { \
throw std::invalid_argument(STRINGIZE(funcName)" : expects exactly 1 string"); \
} \
auto key = arguments[0].asString(runtime).utf8(runtime);

// 设置obj属性
#define SET_PROPERTY(jsiRuntime, name, impl, obj, count) \
auto jsiobj_func = Function::createFromHostFunction(jsiRuntime, PropNameID::forAscii(jsiRuntime, name), count, impl); \
obj.setProperty(jsiRuntime, name, std::move(jsiobj_func));

void setup_get_string(Runtime& jsiRuntime,
                      Object& obj,
                      const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    GET_KEY(count, arguments, runtime, key, get_string)
    optional<std::string> value = get<std::string>(key);
    if (value) {
      return String::createFromUtf8(runtime, value.value());
    } else {
      return Value::undefined();
    }
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_get_int(Runtime& jsiRuntime,
                   Object& obj,
                   const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    GET_KEY(count, arguments, runtime, key, get_int)
    optional<int> value = get<int>(key);
    if (value) {
      return Value(value.value());
    } else {
      return Value::undefined();
    }
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_get_double(Runtime& jsiRuntime,
                      Object& obj,
                      const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    GET_KEY(count, arguments, runtime, key, get_double)
    optional<double> value = get<double>(key);
    if (value) {
      return Value(value.value());
    } else {
      return Value::undefined();
    }
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_get_bool(Runtime& jsiRuntime,
                    Object& obj,
                    const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    GET_KEY(count, arguments, runtime, key, get_bool)
    optional<bool> value = get<bool>(key);
    if (value) {
      return Value(value.value());
    } else {
      return Value::undefined();
    }
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

#define PUT_KEY(arguments, runtime, count, funcName) \
if (count != 2) { \
throw std::invalid_argument(STRINGIZE(funcName)" : multiply expects exactly 2 arguments"); \
} \
if (!arguments[0].isString()) { \
throw std::invalid_argument(STRINGIZE(funcName)" : multiply expects exactly a String for key"); \
} \
auto key = arguments[0].asString(runtime).utf8(runtime); \
if (key == "") { \
throw std::invalid_argument(STRINGIZE(funcName)" : invalid key with empty string"); \
}

void setup_put_string(Runtime& jsiRuntime,
                      Object& obj,
                      const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    PUT_KEY(arguments, runtime, count, put_string)
    if (!arguments[1].isString()) {
      throw std::invalid_argument("multiply expects exactly a String for value");
    }
    auto value = arguments[1].asString(runtime).utf8(runtime);
    auto result = put<std::string>(key, value);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 2)
}

void setup_put_int(Runtime& jsiRuntime,
                   Object& obj,
                   const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    PUT_KEY(arguments, runtime, count, put_int)
    if (!arguments[1].isNumber()) {
      throw std::invalid_argument("put_int: multiply expects exactly a Number for value");
    }
    auto value = static_cast<int>(arguments[1].asNumber());
    auto result = put<int>(key, value);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 2)
}

void setup_put_double(Runtime& jsiRuntime,
                      Object& obj,
                      const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    PUT_KEY(arguments, runtime, count, put_double)
    if (!arguments[1].isNumber()) {
      throw std::invalid_argument("put_double: multiply expects exactly a Number for value");
    }
    auto value = arguments[1].asNumber();
    auto result = put<double>(key, value);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 2)
}

void setup_put_bool(Runtime& jsiRuntime,
                    Object& obj,
                    const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    PUT_KEY(arguments, runtime, count, put_bool)
    if (!arguments[1].isBool()) {
      throw std::invalid_argument("put_bool: multiply expects exactly a Number for value");
    }
    auto value = arguments[1].getBool();
    auto result = put<bool>(key, value);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 2)
}

void setup_put_ints(Runtime& jsiRuntime,
                    Object& obj,
                    const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    if (count != 1) {
      throw std::invalid_argument("put_ints : expects exactly 1 arguments");
    }
    if (!(arguments[0].isObject() && arguments[0].asObject(runtime).isArray(runtime))) {
      throw std::invalid_argument("put_ints : expects exactly a array Object");
    }
    auto list = arguments[0].asObject(runtime).asArray(runtime);
    auto size = list.size(runtime);
    std::vector<std::pair<std::string, int>> kvs;
    kvs.reserve(size);
    for (size_t i = 0; i < size; ++i) {
      auto pairObj = list.getValueAtIndex(runtime, i);
      if (!pairObj.isObject()) {
        throw std::invalid_argument("put_ints : expects exactly a Object in array");
      }
      auto pair = pairObj.asObject(runtime);
      if (!(pair.hasProperty(runtime, "key") && pair.hasProperty(runtime, "value"))) {
        throw std::invalid_argument("put_ints : expects exactly a 'type' and 'value' in a object of array item");
      }
      auto keyProperty = pair.getProperty(runtime, "key");
      auto valueProperty = pair.getProperty(runtime, "value");
      if (!(keyProperty.isString() && valueProperty.isNumber())) {
        throw std::invalid_argument("put_ints : expects exactly a 'type' as string  and 'value' as int in a object of array item");
      }
      auto key = keyProperty.asString(runtime).utf8(runtime);
      auto value = static_cast<int>(valueProperty.asNumber());
      kvs.emplace_back(std::pair<std::string, int>{key, value});
    }
    auto result = put(kvs);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_put_doubles(Runtime& jsiRuntime,
                       Object& obj,
                       const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    if (count != 1) {
      throw std::invalid_argument("put_doubles : expects exactly 1 arguments");
    }
    if (!(arguments[0].isObject() && arguments[0].asObject(runtime).isArray(runtime))) {
      throw std::invalid_argument("put_doubles : expects exactly a array Object");
    }
    auto list = arguments[0].asObject(runtime).asArray(runtime);
    auto size = list.size(runtime);
    std::vector<std::pair<std::string, double>> kvs;
    kvs.reserve(size);
    for (size_t i = 0; i < size; ++i) {
      auto pairObj = list.getValueAtIndex(runtime, i);
      if (!pairObj.isObject()) {
        throw std::invalid_argument("put_doubles : expects exactly a Object in array");
      }
      auto pair = pairObj.asObject(runtime);
      if (!(pair.hasProperty(runtime, "key") && pair.hasProperty(runtime, "value"))) {
        throw std::invalid_argument("put_doubles : expects exactly a 'type' and 'value' in a object of array item");
      }
      auto keyProperty = pair.getProperty(runtime, "key");
      auto valueProperty = pair.getProperty(runtime, "value");
      if (!(keyProperty.isString() && valueProperty.isNumber())) {
        throw std::invalid_argument("put_doubles : expects exactly a 'type' as string  and 'value' as double in a object of array item");
      }
      auto key = keyProperty.asString(runtime).utf8(runtime);
      auto value = valueProperty.asNumber();
      kvs.emplace_back(std::pair<std::string, double>{key, value});
    }
    auto result = put(kvs);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_put_bools(Runtime& jsiRuntime,
                     Object& obj,
                     const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    if (count != 1) {
      throw std::invalid_argument("put_bools : expects exactly 1 arguments");
    }
    if (!(arguments[0].isObject() && arguments[0].asObject(runtime).isArray(runtime))) {
      throw std::invalid_argument("put_bools : expects exactly a array Object");
    }
    auto list = arguments[0].asObject(runtime).asArray(runtime);
    auto size = list.size(runtime);
    std::vector<std::pair<std::string, bool>> kvs;
    kvs.reserve(size);
    for (size_t i = 0; i < size; ++i) {
      auto pairObj = list.getValueAtIndex(runtime, i);
      if (!pairObj.isObject()) {
        throw std::invalid_argument("put_bools : expects exactly a Object in array");
      }
      auto pair = pairObj.asObject(runtime);
      if (!(pair.hasProperty(runtime, "key") && pair.hasProperty(runtime, "value"))) {
        throw std::invalid_argument("put_bools : expects exactly a 'type' and 'value' in a object of array item");
      }
      auto keyProperty = pair.getProperty(runtime, "key");
      auto valueProperty = pair.getProperty(runtime, "value");
      if (!(keyProperty.isString() && valueProperty.isBool())) {
        throw std::invalid_argument("put_bools : expects exactly a 'type' as string  and 'value' as boolean in a object of array item");
      }
      auto key = keyProperty.asString(runtime).utf8(runtime);
      auto value = valueProperty.getBool();
      kvs.emplace_back(std::move(key), value);
    }
    auto result = put(kvs);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_put_strings(Runtime& jsiRuntime,
                       Object& obj,
                       const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    if (count != 1) {
      throw std::invalid_argument("put_strings : expects exactly 1 arguments");
    }
    if (!(arguments[0].isObject() && arguments[0].asObject(runtime).isArray(runtime))) {
      throw std::invalid_argument("put_strings : expects exactly a array Object");
    }
    auto list = arguments[0].asObject(runtime).asArray(runtime);
    auto size = list.size(runtime);
    std::vector<std::pair<std::string, std::string>> kvs;
    kvs.reserve(size);
    for (size_t i = 0; i < size; ++i) {
      auto pairObj = list.getValueAtIndex(runtime, i);
      if (!pairObj.isObject()) {
        throw std::invalid_argument("put_strings : expects exactly a Object in array");
      }
      auto pair = pairObj.asObject(runtime);
      if (!(pair.hasProperty(runtime, "key") && pair.hasProperty(runtime, "value"))) {
        throw std::invalid_argument("put_strings : expects exactly a 'type' and 'value' in a object of array item");
      }
      auto keyProperty = pair.getProperty(runtime, "key");
      auto valueProperty = pair.getProperty(runtime, "value");
      if (!(keyProperty.isString() && valueProperty.isString())) {
        throw std::invalid_argument("put_strings : expects exactly a 'type' as string  and 'value' as string in a object of array item");
      }
      auto key = keyProperty.asString(runtime).utf8(runtime);
      auto value = valueProperty.asString(runtime).utf8(runtime);
      kvs.emplace_back(std::pair<std::string, std::string>{key, value});
    }
    auto result = put(kvs);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_get_json(Runtime& jsiRuntime,
                    Object& obj,
                    const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    GET_KEY(count, arguments, runtime, key, get_json)
    optional<std::string> value = get_json(key);
    if (value) {
      return String::createFromUtf8(runtime, value.value());
    } else {
      return Value::undefined();
    }
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 1)
}

void setup_put_json(Runtime& jsiRuntime,
                    Object& obj,
                    const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    PUT_KEY(arguments, runtime, count, put_json)
    if (!arguments[1].isString()) {
      throw std::invalid_argument("put_json: multiply expects exactly a String for value");
    }
    auto value = arguments[1].asString(runtime);
    auto result = put_json(key, value.utf8(runtime));
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 2)
}

void setup_modify_json(Runtime& jsiRuntime,
                       Object& obj,
                       const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    if (count != 3) {
      throw std::invalid_argument("modify_json: multiply expects exactly 2 arguments");
    }
    if (!arguments[0].isString()) {
      throw std::invalid_argument("modify_json: multiply expects exactly a String for key");
    }
    auto key = arguments[0].asString(runtime).utf8(runtime);
    if (key == "") {
      throw std::invalid_argument("modify_json: : invalid key with empty string");
    }
    if (!arguments[1].isString() || !arguments[1].isString()) {
      throw std::invalid_argument("modify_json: multiply expects exactly a String for value");
    }
    auto path = arguments[1].asString(runtime).utf8(runtime);
    if (path == "") {
      throw std::invalid_argument("modify_json: : invalid path with empty string");
    }
    auto value = arguments[2].asString(runtime).utf8(runtime);
    auto result = modify_json(key, path, value);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 3)
}

void setup_patch_json(Runtime& jsiRuntime,
                      Object& obj,
                      const char *name) {
  auto impl = [](Runtime& runtime, const Value& thisValue, const Value* arguments, size_t count) -> Value {
    PUT_KEY(arguments, runtime, count, patch_json)
    if (!arguments[1].isString()) {
      throw std::invalid_argument("patch_json: multiply expects exactly a String for value");
    }
    auto value =arguments[1].asString(runtime).utf8(runtime);
    auto result = patch_json(key, value);
    return Value(result == 101);
  };
  SET_PROPERTY(jsiRuntime, name, impl, obj, 2)
}

// This is the function that will be called by the host application to register the module
void install(facebook::jsi::Runtime& runtime) {
  facebook::jsi::Object obj{runtime};
  setup_jsimultiply(runtime, obj, "jsimultiply");
  setup_get_string(runtime, obj, "getString");
  setup_get_int(runtime, obj, "getInt");
  setup_get_double(runtime, obj, "getDouble");
  setup_get_bool(runtime, obj, "getBoolean");
  setup_put_string(runtime, obj, "putString");
  setup_put_int(runtime, obj, "putInt");
  setup_put_double(runtime, obj, "putDouble");
  setup_put_bool(runtime, obj, "putBoolean");
  setup_put_strings(runtime, obj, "putStrings");
  setup_put_ints(runtime, obj, "putInts");
  setup_put_doubles(runtime, obj, "putDoubles");
  setup_put_bools(runtime, obj, "putBooleans");
  setup_get_json(runtime, obj, "getJson");
  setup_put_json(runtime, obj, "putJson");
  setup_modify_json(runtime, obj, "modifyJson");
  setup_patch_json(runtime, obj, "patchJson");
  runtime.global().setProperty(runtime, "memcachejsi", std::move(obj));
}
}
