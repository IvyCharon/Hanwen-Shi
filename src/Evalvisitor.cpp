#include "Evalvisitor.h"

std::map<std::string,alltype> values;
std::map<std::string,Afunc> functions;
std::vector<ConBreRet> go;
std::stack<std::map<std::string,alltype>> func_maps;
std::stack<std::vector<alltype>> Rets;

std::map<std::string,alltype> & findmap(std::string name)
{
    if(func_maps.empty() || func_maps.top().find(name) == func_maps.top().end()) return values;
    else return func_maps.top();
}

antlrcpp::Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx)
{
    Afunc tmpfunc;
    tmpfunc.name = ctx -> NAME() -> toString();
    tmpfunc.suit = ctx -> suite();
    if(visitParameters(ctx -> parameters()).is<std::vector<para>>())
        tmpfunc.paralist = visitParameters(ctx -> parameters()).as<std::vector<para>>();
    if(functions.find(tmpfunc.name) != functions.end())
        functions[tmpfunc.name] = tmpfunc;
    else functions.insert(std::pair<std::string,Afunc>(tmpfunc.name,tmpfunc));
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx)
{
    if(ctx -> typedargslist() != nullptr)return visitTypedargslist(ctx -> typedargslist());
    else
    {
        std::vector<para> tmp;
        return tmp;
    }
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx)
{
    std::vector<para> ans;
    int numOfName, numOfTest;
    numOfName = ctx -> tfpdef().size();
    numOfTest = ctx -> test().size();
    for(int i = 0;i <= numOfName - numOfTest - 1;++ i)
        ans.push_back(visitTfpdef(ctx -> tfpdef(i)));
    for(int i = numOfName - numOfTest,j = 0;i <= numOfName - 1;++ i,++ j)
    {
        para tmp;
        tmp = visitTfpdef(ctx -> tfpdef(i));
        tmp.it = visitTest(ctx -> test(j));
        ans.push_back(tmp);
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx)
{
    para tmp;
    tmp.name = ctx -> NAME() -> toString();
    return tmp;
}

antlrcpp::Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx)
{
    if(ctx -> simple_stmt() != nullptr)return visitSimple_stmt(ctx -> simple_stmt());
    if(ctx -> compound_stmt() != nullptr)return visitCompound_stmt(ctx -> compound_stmt());
}

antlrcpp::Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx)
{
    return visitSmall_stmt(ctx -> small_stmt());
}

antlrcpp::Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx)
{
    if(ctx -> expr_stmt() != nullptr)return visitExpr_stmt(ctx -> expr_stmt());
    if(ctx -> flow_stmt() != nullptr)return visitFlow_stmt(ctx -> flow_stmt());
}

antlrcpp::Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx)
{
    if(ctx -> augassign() == nullptr && ctx -> ASSIGN().size() == 0)
        return visitTestlist(ctx -> testlist(0));
    else if(ctx -> augassign() != nullptr)
    {
        int op = visitAugassign(ctx -> augassign()).as<int>();
        std::vector<alltype> a, b;
        a = visitTestlist(ctx -> testlist(0)).as<std::vector<alltype> >();
        b = visitTestlist(ctx -> testlist(1)).as<std::vector<alltype> >();
        for(int i = 0;i < a.size();++ i)
        {
            switch(op)
            {
                case 0:
                    findmap(a[i].name)[a[i].name] = findmap(a[i].name)[a[i].name] + b[i];
                    break;
                case 1:
                    findmap(a[i].name)[a[i].name] = findmap(a[i].name)[a[i].name] - b[i];
                    break;
                case 2:
                    findmap(a[i].name)[a[i].name] = findmap(a[i].name)[a[i].name] * b[i];
                    break;
                case 3:
                    findmap(a[i].name)[a[i].name] = (double)findmap(a[i].name)[a[i].name] / (double)b[i];
                    break;
                case 4:
                    findmap(a[i].name)[a[i].name] = findmap(a[i].name)[a[i].name] / b[i];
                    if(findmap(a[i].name)[a[i].name].now == 2)
                    {
                        findmap(a[i].name)[a[i].name].now = 0;
                        findmap(a[i].name)[a[i].name].type0 = (integer)findmap(a[i].name)[a[i].name].type2;
                        findmap(a[i].name)[a[i].name].type2 = NULL;
                    }
                    break;
                case 5:
                    findmap(a[i].name)[a[i].name] = findmap(a[i].name)[a[i].name] % b[i];
                    break;
            }
            findmap(a[i].name)[a[i].name].name = a[i].name;
        }
        return nullptr;
    }
    if(ctx -> ASSIGN().size() != 0)
    {
        std::vector<alltype> a,b;
        b = visitTestlist(ctx -> testlist(ctx -> testlist().size() - 1)).as<std::vector<alltype>>();
        for(int i = ctx -> ASSIGN().size() - 1;i >= 0;-- i)
        {
            a = visitTestlist(ctx -> testlist(i)).as<std::vector<alltype>>();
            if(func_maps.empty())
            {
                for(int j = 0;j < a.size();++ j)
                {
                    if(values.find(a[j].name) == values.end())
                    {
                        alltype tmp = b[j];
                        tmp.name = a[j].name;
                        values.insert(std::pair<std::string,alltype>(tmp.name,tmp));
                    }
                    else
                    {
                        std::string tmp = a[j].name;
                        values[a[j].name] = b[j];
                        values[tmp].name = tmp;
                    }
                }
            }
            else
            {
                for(int j = 0;j < a.size();++ j)
                {
                    if(func_maps.top().find(a[j].name) == func_maps.top().end())
                    {
                        alltype tmp = b[j];
                        tmp.name = a[j].name;
                        func_maps.top().insert(std::pair<std::string,alltype>(tmp.name,tmp));
                    }
                    else
                    {
                        std::string tmp = a[j].name;
                        func_maps.top()[a[j].name] = b[j];
                        func_maps.top()[tmp].name = tmp;
                    }
                }
            }
        }
        return nullptr;
    }
}

antlrcpp::Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx)
{
    if(ctx -> ADD_ASSIGN() != nullptr)return 0;
    if(ctx -> SUB_ASSIGN() != nullptr)return 1;
    if(ctx -> MULT_ASSIGN() != nullptr)return 2;
    if(ctx -> DIV_ASSIGN() != nullptr)return 3;
    if(ctx -> IDIV_ASSIGN() != nullptr)return 4;
    if(ctx -> MOD_ASSIGN() != nullptr)return 5;
}

antlrcpp::Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx)
{
    if(ctx -> break_stmt() != nullptr)return visitBreak_stmt(ctx -> break_stmt());
    if(ctx -> continue_stmt() != nullptr)return visitContinue_stmt(ctx -> continue_stmt());
    if(ctx -> return_stmt() != nullptr)return visitReturn_stmt(ctx -> return_stmt());
}

antlrcpp::Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx)
{
    if(ctx -> BREAK() != nullptr)
        go[go.size() - 1].upBre = 1;
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx)
{
    if(ctx -> CONTINUE() != nullptr)
        go[go.size() - 1].upCon = 1;
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx)
{
    if(ctx -> RETURN() != nullptr)
        go[go.size() - 1].upRet = 1;
    std::vector<alltype> tmp;
    if(ctx -> testlist() != nullptr)
        Rets.top() = visitTestlist(ctx -> testlist()).as<std::vector<alltype>>();
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx)
{
    if(ctx -> while_stmt() != nullptr)return visitWhile_stmt(ctx -> while_stmt());
    if(ctx -> if_stmt() != nullptr)return visitIf_stmt(ctx -> if_stmt());
    if(ctx -> funcdef() != nullptr)return visitFuncdef(ctx -> funcdef());
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx)
{
    ConBreRet mm;
    mm.NOW = ctx -> IF();
    go.push_back(mm);
    for(int i = 0;i < ctx -> test().size();++ i)
    {
        if(visitTest(ctx -> test(i)).as<alltype>())
        {
            visitSuite(ctx -> suite(i));
            go.pop_back();
            return nullptr;
        }
    }
    if(ctx -> ELSE() != nullptr)
    {
        visitSuite(ctx -> suite(ctx -> suite().size() - 1));
        go.pop_back();
        return nullptr;
    }
    go.pop_back();
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx)
{
    ConBreRet lp(ctx -> WHILE());
    go.push_back(lp);
    alltype j = visitTest(ctx -> test()).as<alltype>();
    while(j)
    {
        visitSuite(ctx -> suite());
        if(go[go.size() - 1].upBre || go[go.size() - 1].upRet) break;
        j = visitTest(ctx -> test()).as<alltype>();
    }
    go.pop_back();
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx)
{
    if(ctx -> simple_stmt() != nullptr)return visitSimple_stmt(ctx -> simple_stmt());
    for(int i = 0;i < ctx -> stmt().size();++ i)
    {
        visitStmt(ctx -> stmt(i));
        if(go[go.size() - 1].upBre || go[go.size() - 1].upCon || go[go.size() - 1].upRet) break;
    }
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx)
{
    return visitOr_test(ctx -> or_test());
}

antlrcpp::Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx)
{
    if(ctx -> and_test().size() == 1)return visitAnd_test(ctx -> and_test(0));
    alltype ans = visitAnd_test(ctx -> and_test(0)).as<alltype>();
    ans.now = 1;
    ans.name = "";
    for(int i = 1;i < ctx -> and_test().size();++ i)
    {
        if(ans.type1)break;
        ans.type1 = ans || visitAnd_test(ctx -> and_test(i)).as<alltype>();
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx)
{
    if(ctx -> not_test().size() == 1)return visitNot_test(ctx -> not_test(0));
    alltype ans = visitNot_test(ctx -> not_test(0)).as<alltype>();
    ans.now = 1;
    ans.name = "";
    for(int i = 1;i < ctx -> not_test().size();++ i)
    {
        if(!ans.type1)break;
        ans.type1 = ans && visitNot_test(ctx -> not_test(i)).as<alltype>();
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx)
{
    if(ctx -> not_test() == nullptr) return visitComparison(ctx->comparison());
    alltype ans;
    ans.now = 1;
    ans.type1 = !visitNot_test(ctx -> not_test()).as<alltype>();
    return ans;
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx)
{
    if(ctx -> comp_op().size() == 0) return visitArith_expr(ctx -> arith_expr(0));
    alltype biu(1,"true");
    alltype gua,wa,last;
    last = visitArith_expr(ctx -> arith_expr(0)).as<alltype>();
    for(int i = 0;i < ctx-> comp_op().size();++ i)
    {
        int k = visitComp_op(ctx -> comp_op(i)).as<int>();
        gua = last;
        wa = visitArith_expr(ctx -> arith_expr(i + 1)).as<alltype>();
        last = wa;
        switch(k)
        {
            case 0:
                if(gua >= wa)biu.type1 = false;
                break;
            case 1:
                if(gua <= wa)biu.type1 = false;
                break;
            case 2:
                if(gua != wa)biu.type1 = false;
                break;
            case 3:
                if(gua < wa)biu.type1 = false;
                break;
            case 4:
                if(gua > wa)biu.type1 = false;
                break;
            case 5:
                if(gua == wa)biu.type1 = false;
                break;
        }
        if(!biu)break;
    }
    return biu;
}

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx)
{
    if(ctx -> LESS_THAN() != nullptr) return 0;
    if(ctx -> GREATER_THAN() != nullptr) return 1;
    if(ctx -> EQUALS() != nullptr) return 2;
    if(ctx -> GT_EQ() != nullptr) return 3;
    if(ctx -> LT_EQ() != nullptr) return 4;
    if(ctx -> NOT_EQ_2() != nullptr) return 5;
}

antlrcpp::Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx)
{
    if(ctx -> term().size() == 1)return visitTerm(ctx -> term(0));
    alltype ans = visitTerm(ctx -> term(0)).as<alltype>();
    for(int i = 0;i < ctx -> addminus().size();++ i)
    {
        int op = visitAddminus(ctx -> addminus(i)).as<int>();
        alltype tmp = visitTerm(ctx -> term(i + 1)).as<alltype>();
        switch(op)
        {
            case 1:
                ans = ans + tmp;
                break;
            case 0:
                ans = ans - tmp;
                break;
        }
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitAddminus(Python3Parser::AddminusContext *ctx)
{
    if(ctx -> ADD() != nullptr)return 1;
    if(ctx -> MINUS() != nullptr)return 0;
}

antlrcpp::Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx)
{
    if(ctx -> muldivmod().size() == 0)return visitFactor(ctx -> factor(0));
    alltype ans = visitFactor(ctx -> factor(0)).as<alltype>();
    for(int i = 0;i < ctx -> muldivmod().size();++ i)
    {
        alltype tmp = visitFactor(ctx -> factor(i + 1)).as<alltype>();
        int op = visitMuldivmod(ctx -> muldivmod(i)).as<int>();
        switch(op) {
            case 0:
                ans = ans * tmp;
                break;
            case 1:
                if(ans.now == 0)
                {
                    ans.type2 = (double)ans.type0;
                    ans.now = 2;
                    ans.type0 = NULL;
                }
                if(ans.now == 1)
                {
                    ans.type2 = (double)ans.type1;
                    ans.now = 2;
                    ans.type1 = NULL;
                }
                if(tmp.now == 0)ans.type2 = ans.type2 / (double)tmp.type0;
                if(tmp.type1)ans.type2 = ans.type2;
                if(tmp.now == 2)ans.type2 = ans.type2 / tmp.type2;
                break;
            case 2:
                ans = ans / tmp;
                if (ans.now == 2)
                {
                    ans.now = 0;
                    ans.type0 = (integer) ans.type2;
                    ans.type2 = NULL;
                }
                break;
            case 3:
                ans = ans % tmp;
                break;
        }
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitMuldivmod(Python3Parser::MuldivmodContext *ctx)
{
    if(ctx -> STAR() != nullptr)return 0;
    if(ctx -> DIV() != nullptr)return 1;
    if(ctx -> IDIV() != nullptr)return 2;
    if(ctx -> MOD() != nullptr)return 3;
}

antlrcpp::Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx)
{
    if(ctx -> factor() != nullptr)
    {
        if(ctx -> ADD() != nullptr)return visitFactor(ctx -> factor());
        else if(ctx -> MINUS() != nullptr)
        {
            alltype ans = - (visitFactor(ctx -> factor()).as<alltype>());
            return ans;
        }
        return visitFactor(ctx -> factor());
    }
    if(ctx -> atom_expr() != nullptr)return visitAtom_expr(ctx -> atom_expr());
}

antlrcpp::Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx)
{
    if(ctx -> trailer() == nullptr)return visitAtom(ctx -> atom());
    else
    {
        alltype tmp;
        tmp = visitAtom(ctx -> atom()).as<alltype>();
        std::vector<alltype> out;
        std::vector<para> zzj;
        if(ctx -> atom() -> NAME() -> toString() == "print")
        {
            zzj = visitTrailer(ctx -> trailer()).as<std::vector<para>>();
            for(int i = 0;i < zzj.size();++ i)
                out.push_back(zzj[i].it);
            for(int i = 0;i < out.size();++ i)
            {
                if(out[i].now == -1) std::cout<<"None";
                else if(out[i].name == "")print(out[i]);
                else print(findmap(out[i].name)[out[i].name]);
                if(i != out.size() - 1)std::cout<<" ";
            }
            std::cout<<std::endl;
            return visitAtom(ctx -> atom());
        }
        else if(ctx -> atom() -> NAME() -> toString() == "int")
        {
            zzj = visitTrailer(ctx -> trailer()).as<std::vector<para>>();
            for(int i = 0;i < zzj.size();++ i)
                out.push_back(zzj[i].it);
            alltype ans;
            alltype tmp = out[0];
            ans.now = 0;
            int op = tmp.now;
            switch(op)
            {
                case 0:
                    ans = tmp;
                    break;
                case 1:
                    if(tmp.type1) ans.type0 = (integer)1;
                    else ans.type0 = (integer)0;
                    break;
                case 2:
                    ans.type0 = (integer)((int)tmp.type2);
                    break;
            }
            return ans;
        }
        else if(ctx -> atom() -> NAME() -> toString() == "float")
        {
            zzj = visitTrailer(ctx -> trailer()).as<std::vector<para>>();
            for(int i = 0;i < zzj.size();++ i)
                out.push_back(zzj[i].it);
            alltype ans;
            alltype tmp = out[0];
            ans.now = 2;
            int op = tmp.now;
            switch (op)
            {
                case 0:
                    ans.type2 = (double)tmp.type0;
                    break;
                case 1:
                    ans.type2 = (double)tmp.type1;
                    break;
            }
            return ans;
        }
        else if(ctx -> atom() -> NAME() -> toString() == "str")
        {
            zzj = visitTrailer(ctx -> trailer()).as<std::vector<para>>();
            for(int i = 0;i < zzj.size();++ i)
                out.push_back(zzj[i].it);
            alltype ans;
            alltype tmp = out[0];
            ans.now = 3;
            int op = tmp.now;
            switch (op)
            {
                case 0:
                    ans.type3 = (std::string)tmp.type0;
                    break;
                case 1:
                    if(tmp.type1)ans.type3 = "True";
                    else ans.type3 = "False";
                    break;
                case 2:
                    ans.type3 = std::to_string(tmp.type2);
                    break;
            }
            return ans;
        }
        else if(ctx -> atom() -> NAME() -> toString() == "bool")
        {
            zzj = visitTrailer(ctx -> trailer()).as<std::vector<para>>();
            for(int i = 0;i < zzj.size();++ i)
                out.push_back(zzj[i].it);
            alltype ans;
            alltype tmp = out[0];
            ans.now = 1;
            if(tmp)ans.type1 = 1;
            else ans.type1 = 0;
            return ans;
        }
        else
        {
            Afunc nowfunc = functions[ctx -> atom() -> NAME() -> toString()];
            std::vector<alltype> lucy;
            Rets.push(lucy);
            ConBreRet yyh;
            go.push_back(yyh);
            std::map<std::string,alltype> nowmap;
            for(int i = 0;i < nowfunc.paralist.size();++ i)
                nowmap.insert(std::pair<std::string,alltype>(nowfunc.paralist[i].name,nowfunc.paralist[i].it));
            zzj = visitTrailer(ctx -> trailer()).as<std::vector<para>>();
            for(int i = 0;i < zzj.size();++ i)
            {
                if(zzj[i].name == "")
                    nowmap[nowfunc.paralist[i].name] = zzj[i].it;
                else
                    nowmap[zzj[i].name] = zzj[i].it;
            }
            func_maps.push(nowmap);
            antlrcpp::Any cjh = visitSuite(nowfunc.suit);
            func_maps.pop();
            go.pop_back();
            std::vector<alltype> tmp = Rets.top();
            Rets.pop();
            if(tmp.size() == 1)return tmp[0];
            if(tmp.size() == 0)
            {
                alltype zzy;
                return zzy;
            }
            else return tmp;
        }
    }
}

antlrcpp::Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx)
{
    if(ctx -> arglist() != nullptr)return visitArglist(ctx -> arglist());
    std::vector<para> tmp;
    return tmp;
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx)
{
    alltype ans;
    if(ctx -> FALSE() != nullptr)
    {
        ans.now = 1;
        ans.type1 = 0;
        return ans;
    }
    if(ctx -> TRUE() != nullptr)
    {
        ans.now = 1;
        ans.type1 = 1;
        return ans;
    }
    if(ctx -> CLOSE_PAREN() != nullptr)
        return visitTest(ctx -> test());
    if(ctx -> NONE() != nullptr)
        return ans;
    if(ctx -> NAME() != nullptr)
    {
        ans.name = ctx -> NAME() -> toString();
        if(!func_maps.empty())
        {
            if(func_maps.top().find(ans.name) == func_maps.top().end())
            {
                func_maps.top().insert(std::pair<std::string,alltype>(ans.name,ans));
                return ans;
            }
            else
            {
                ans = func_maps.top()[ans.name];
                return ans;
            }
        }
        else
        {
            if(values.find(ans.name) == values.end())
            {
                values.insert(std::pair<std::string,alltype>(ans.name,ans));
                return ans;
            }
            else
            {
                ans = values[ans.name];
                return ans;
            }
        }
    }
    if(ctx -> NUMBER() != nullptr)
    {
        std::string k = ctx -> NUMBER() -> toString();
        bool fori = 1;
        for(int i = 0;i < k.length();++ i)
        {
            if(k[i] == '.')
            {
                fori = 0;
                break;
            }
        }
        if(fori)
        {
            alltype ans;
            ans.now = 0;
            ans.type0 = (integer)ctx -> NUMBER() -> toString();
            return ans;
        }
        else
        {
            alltype ans(2,ctx -> NUMBER() -> toString());
            return ans;
        }
    }
    if(ctx -> STRING().size() != 0)
    {
        alltype ans;
        ans.now = 3;
        std::string k = "";
        for(int i = 0;i < ctx -> STRING().size();++ i)
        {
            std::string l;
            l = ctx -> STRING()[i] -> toString();
            for(int j = 1;j < l.length() - 1;++ j)
                k += l[j];
        }
        ans.type3 = k;
        return ans;
    }
}

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx)
{
    std::vector<alltype> ans;
    int n = ctx -> test().size();
    for(int i = 0 ; i < n ; ++ i)
        ans.push_back(visitTest(ctx -> test(i)).as<alltype>());
    return ans;
}

antlrcpp::Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx)
{
    std::vector<para> ans;
    para tmp;
    for(int i = 0;i < ctx -> argument().size();++ i)
    {
        tmp = visitArgument(ctx -> argument(i)).as<para>();
        ans.push_back(tmp);
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx)
{
    para tmp;
    if(ctx -> NAME() == nullptr)
    {
        tmp.it = visitTest(ctx -> test()).as<alltype>();
        return tmp;
    }
    else
    {
        tmp.name = ctx -> NAME() -> toString();
        tmp.it = visitTest(ctx -> test()).as<alltype>();
        return tmp;
    }
}