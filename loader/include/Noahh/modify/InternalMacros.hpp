#include <type_traits>

/**
 * Main class implementation, it has the structure
 * 
 * class hook0Dummy;
 * template<typename>
 * struct hook0 {};
 * namespace {
 *     struct hook0Parent {};
 *     Modify<hook0<hook0Parent>, MenuLayer> hook0Apply;
 *     struct NOAHH_HIDDEN hook0Intermediate: public MenuLayer {
 *         noahh::modifier::FieldIntermediate<MenuLayer,
 *             hook0<hook0Intermediate>, hook0<hook0Parent>
 *         > m_fields;
 *     };
 * }
 * template<>
 * struct NOAHH_HIDDEN hook0<hook0Parent>: hook0Intermediate {
 *     // code stuff idk
 * };
 * 
 * I tried to make the macro as verbose as it can be but
 * I am bad at this stuff
 */

#define NOAHH_MODIFY_DECLARE_ANONYMOUS(base, derived)                             \
derived##Dummy;                                                                   \
template<class> struct derived {};                                                \
namespace {                                                                       \
	struct derived##Parent {};                                                    \
	Modify<derived<derived##Parent>, base> derived##Apply;                        \
	struct NOAHH_HIDDEN derived##Intermediate : base {                            \
		noahh::modifier::FieldIntermediate<base,                                  \
			derived##Intermediate,                                                \
			derived<derived##Parent>                                              \
		> m_fields;                                                               \
	};                                                                            \
}                                                                                 \
template <> struct NOAHH_HIDDEN derived<derived##Parent> : derived##Intermediate  \
   
#define NOAHH_MODIFY_DECLARE(base, derived)                                       \
derived##Dummy;                                                                   \
struct derived;                                                                   \
namespace {                                                                       \
	Modify<derived, base> derived##Apply;                                         \
	struct NOAHH_HIDDEN derived##Intermediate : base {                            \
		noahh::modifier::FieldIntermediate<base,                                  \
			derived##Intermediate,                                                \
			derived                                                               \
		> m_fields;                                                               \
	};                                                                            \
}                                                                                 \
struct NOAHH_HIDDEN derived : derived##Intermediate                               \

#define NOAHH_MODIFY_REDIRECT4(base, derived) NOAHH_MODIFY_DECLARE(base, derived)
#define NOAHH_MODIFY_REDIRECT3(base, derived) NOAHH_MODIFY_DECLARE_ANONYMOUS(base, derived)
#define NOAHH_MODIFY_REDIRECT2(base) NOAHH_MODIFY_REDIRECT3(base, NOAHH_CONCAT(hook, __LINE__))
#define NOAHH_MODIFY_REDIRECT1(base) NOAHH_MODIFY_REDIRECT2(base)

/**
 * Interfaces for the class implementation
 * 
 * class $modify(MenuLayer) {};
 * class $modify(MyMenuLayerInterface, MenuLayer) {};
 */

#define NOAHH_CRTP1(base) NOAHH_MODIFY_REDIRECT1(base)
#define NOAHH_CRTP2(derived, base) NOAHH_MODIFY_REDIRECT4(base, derived)
#define $modify(...) NOAHH_INVOKE(NOAHH_CONCAT(NOAHH_CRTP, NOAHH_NUMBER_OF_ARGS(__VA_ARGS__)), __VA_ARGS__)
#define $(...) $modify(__VA_ARGS__)


/**
 * Get current hook class without needing to name it.
 * Useful for callbacks
 */
#define $cls std::remove_pointer<decltype(this)>::type

#define NOAHH_ONLY_FIELD(type, field_, default_) private: field<type> field_ = default_; public:
#define NOAHH_INTERNAL_FIELD(type, field, name) inline type& name() { return this->*field; }
//#define NOAHH_EXTERNAL_FIELD(type, field, name) static inline type& name##From(void* self) { return reinterpret_cast<decltype(this)>(self)->*field; }
#define NOAHH_FIELD(type, field, name, default_) NOAHH_ONLY_FIELD(type, field, default_) NOAHH_INTERNAL_FIELD(type, field, name) //NOAHH_EXTERNAL_FIELD(type, field, name)


#define NOAHH_EXECUTE_FUNC(Line_)                                 \
template<class>                                                   \
void _##Line_##Function();                                        \
namespace {                                                       \
	struct _##Line_##Unique {};                                   \
}                                                                 \
static inline auto _line = (Interface::get()->scheduleOnLoad(     \
	&_##Line_##Function<_##Line_##Unique>                         \
), 0);                                                            \
template<class>                                                   \
void _##Line_##Function()

#define $execute NOAHH_EXECUTE_FUNC(__LINE__)