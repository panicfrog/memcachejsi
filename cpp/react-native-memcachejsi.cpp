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
      auto value = arguments[1].asNumber();
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
    setup_get_json(runtime, obj, "getJson");
    setup_put_json(runtime, obj, "putJson");
    setup_modify_json(runtime, obj, "modifyJson");
    setup_patch_json(runtime, obj, "patchJson");
    runtime.global().setProperty(runtime, "memcachejsi", std::move(obj));
	}
}
