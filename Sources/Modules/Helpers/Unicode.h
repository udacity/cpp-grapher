#ifndef UNICODE_H
#define UNICODE_H

#include "tinyutf8.h"

class UnicodeLiterals
{
public:
    //All whitespace literals in Unicode v7.0
    static constexpr utf8_string::value_type CHARACTER_TABULATION = 0x0009; //Unicode Cc class
    static constexpr utf8_string::value_type LINE_FEED = 0x000a; //Unicode Cc class
    static constexpr utf8_string::value_type LINE_TABULATION = 0x000b; //Unicode Cc class
    static constexpr utf8_string::value_type FORM_FEED = 0x000c; //Unicode Cc class
    static constexpr utf8_string::value_type CARRIAGE_RETURN = 0x000d; //Unicode Cc class
    static constexpr utf8_string::value_type SPACE = 0x0020; //Unicode Zs class
    static constexpr utf8_string::value_type NO_BREAK_SPACE = 0xa0; //Unicode Zs class
    static constexpr utf8_string::value_type OGHAM_SPACE_MARK = 0x1680; //Unicode Zs class
    static constexpr utf8_string::value_type EN_QUAD = 0x2000; //Unicode Zs class
    static constexpr utf8_string::value_type EM_QUAD = 0x2001; //Unicode Zs class
    static constexpr utf8_string::value_type EN_SPACE = 0x2002; //Unicode Zs class
    static constexpr utf8_string::value_type EM_SPACE = 0x2003; //Unicode Zs class
    static constexpr utf8_string::value_type THREE_PER_EM_SPACE = 0x2004; //Unicode Zs class
    static constexpr utf8_string::value_type FOUR_PER_EM_SPACE = 0x2005; //Unicode Zs class
    static constexpr utf8_string::value_type SIX_PER_EM_SPACE = 0x2006; //Unicode Zs class
    static constexpr utf8_string::value_type FIGURE_SPACE = 0x2007; //Unicode Zs class
    static constexpr utf8_string::value_type PUNCTUATION_SPACE = 0x2008; //Unicode Zs class
    static constexpr utf8_string::value_type THIN_SPACE = 0x2009; //Unicode Zs class
    static constexpr utf8_string::value_type HAIR_SPACE = 0x200a; //Unicode Zs class
    static constexpr utf8_string::value_type ZERO_WIDTH_SPACE = 0x200b; //Unicode Cf class
    static constexpr utf8_string::value_type LINE_SEPARATOR = 0x2028; //Unicode Zl class
    static constexpr utf8_string::value_type PARAGRAPH_SEPARATOR = 0x2029; //Unicode Zp class
    static constexpr utf8_string::value_type NARROW_NO_BREAK_SPACE = 0x202f; //Unicode Zs class
    static constexpr utf8_string::value_type MEDIUM_MATHEMATICAL_SPACE = 0x205f; //Unicode Zs class
    static constexpr utf8_string::value_type IDEOGRAPHIC_SPACE = 0x3000; //Unicode Zs class

    static constexpr utf8_string::value_type WHITESPACE[] { UnicodeLiterals::SPACE,
                                                            UnicodeLiterals::CHARACTER_TABULATION,
                                                            UnicodeLiterals::LINE_FEED,
                                                            UnicodeLiterals::CARRIAGE_RETURN,
                                                            UnicodeLiterals::LINE_TABULATION,
                                                            UnicodeLiterals::FORM_FEED,
                                                            UnicodeLiterals::NO_BREAK_SPACE,
                                                            UnicodeLiterals::OGHAM_SPACE_MARK,
                                                            UnicodeLiterals::EN_QUAD,
                                                            UnicodeLiterals::EM_QUAD,
                                                            UnicodeLiterals::EN_SPACE,
                                                            UnicodeLiterals::EM_SPACE,
                                                            UnicodeLiterals::THREE_PER_EM_SPACE,
                                                            UnicodeLiterals::FOUR_PER_EM_SPACE,
                                                            UnicodeLiterals::SIX_PER_EM_SPACE,
                                                            UnicodeLiterals::FIGURE_SPACE,
                                                            UnicodeLiterals::PUNCTUATION_SPACE,
                                                            UnicodeLiterals::THIN_SPACE,
                                                            UnicodeLiterals::HAIR_SPACE,
                                                            UnicodeLiterals::ZERO_WIDTH_SPACE,
                                                            UnicodeLiterals::LINE_SEPARATOR,
                                                            UnicodeLiterals::PARAGRAPH_SEPARATOR,
                                                            UnicodeLiterals::NARROW_NO_BREAK_SPACE,
                                                            UnicodeLiterals::MEDIUM_MATHEMATICAL_SPACE,
                                                            UnicodeLiterals::IDEOGRAPHIC_SPACE };
};

constexpr utf8_string::value_type UnicodeLiterals::WHITESPACE[];

#endif //UNICODE_H
