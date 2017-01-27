/*
 Copyright (C) 2010-2017 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LegacyModelDefinitionParser_h
#define LegacyModelDefinitionParser_h

#include "IO/Parser.h"
#include "IO/Token.h"
#include "IO/Tokenizer.h"

namespace TrenchBroom {
    namespace EL {
        class Expression;
        class ExpressionBase;
    }
    
    namespace IO {
        class ParserStatus;
        
        namespace MdlToken {
            typedef size_t Type;
            static const Type Integer       = 1 << 0;
            static const Type Equality      = 1 << 1;
            static const Type Word          = 1 << 2;
            static const Type String        = 1 << 3;
            static const Type Comma         = 1 << 4;
            static const Type CParenthesis  = 1 << 5;
            static const Type Eof           = 1 << 6;
        }
        
        class LegacyModelDefinitionTokenizer : public Tokenizer<MdlToken::Type> {
        public:
            LegacyModelDefinitionTokenizer(const char* begin, const char* end);
            LegacyModelDefinitionTokenizer(const String& str);
            
            template <typename OtherToken>
            LegacyModelDefinitionTokenizer(Tokenizer<OtherToken>& nestedTokenizer) :
            Tokenizer(nestedTokenizer) {}
        private:
            static const String WordDelims;
            Token emitToken();
        };
        
        class LegacyModelDefinitionParser : public Parser<MdlToken::Type> {
        private:
            typedef LegacyModelDefinitionTokenizer::Token Token;
            LegacyModelDefinitionTokenizer m_tokenizer;
        public:
            LegacyModelDefinitionParser(const char* begin, const char* end);
            LegacyModelDefinitionParser(const String& str);
            
            template <typename OtherToken>
            LegacyModelDefinitionParser(Tokenizer<OtherToken>& nestedTokenizer) :
            m_tokenizer(nestedTokenizer) {}
        public:
            EL::Expression parse(ParserStatus& status);
        private:
            EL::Expression parseModelDefinition(ParserStatus& status);
            EL::ExpressionBase* parseStaticModelDefinition(ParserStatus& status);
            EL::ExpressionBase* parseDynamicModelDefinition(ParserStatus& status);
            EL::ExpressionBase* parseNamedValue(ParserStatus& status, const String& name);
        private:
            TokenNameMap tokenNames() const;
        };
    }
}

#endif /* LegacyModelDefinitionParser_h */
