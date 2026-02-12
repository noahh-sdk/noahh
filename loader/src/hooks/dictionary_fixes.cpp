// #include <Noahh/Noahh.hpp>
// // this is the fix for the dynamic_cast problems

// USE_NOAHH_NAMESPACE();

// #if defined(NOAHH_IS_IOS) || defined(NOAHH_IS_MACOS)
// namespace noahh::fixes {
// 	using namespace noahh::cast;


// class $modify(CCDictionaryTypeinfoFix, CCDictionary) {
// 	const CCString* valueForKey(const gd::string& key) {
// 		CCString* pStr = dynamic_cast<CCString*>(objectForKey(key));
// 	    if (pStr == nullptr) {
// 	        pStr = const_cast<CCString*>(CCDictionary::valueForKey(key));
// 	    }
// 	    return pStr;
// 	}

// 	const CCString* valueForKey(intptr_t key) {
// 		CCString* pStr = dynamic_cast<CCString*>(objectForKey(key));
// 	    if (pStr == nullptr) {
// 	        pStr = const_cast<CCString*>(CCDictionary::valueForKey(key));
// 	    }
// 	    return pStr;
// 	}
// };

// } // noahh::fixes

// #endif