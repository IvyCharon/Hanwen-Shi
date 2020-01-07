#include "Evalvisitor.h"

std::map<std::string,alltype> values;
std::vector<ConBreRet> go;
//std::stack<std::map<std::string,alltype> > maps;
//std::map<std::string,funs> fmap;
//funs nowfunc;
//int nowf = 0;

antlrcpp::Any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx)//
{
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx)//
{
    /*std::string na = ctx -> NAME() -> toString();
    funs ftmp;
    ftmp.fname = na;
    ftmp.fsuite = ctx -> suite();
    ftmp.ftypelist = visitParameters(ctx -> parameters()).as<std::vector<alltype> >();
    fmap.insert(std::pair<std::string,funs>(ftmp.fname,ftmp));*/
    //return nullptr;
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitParameters(Python3Parser::ParametersContext *ctx)//
{
    //if(ctx ->typedargslist() != nullptr) return visitTypedargslist(ctx -> typedargslist());
    //else return std::vector<alltype>(0);
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTypedargslist(Python3Parser::TypedargslistContext *ctx)//
{
    /*std::vector<alltype> ans;
    std::string k;
    alltype tmp;
    for(int i = 0;i < ctx -> test().size();++ i)
    {
        k = visitTfpdef(ctx -> tfpdef(i)).as<std::string>();
        tmp = visitTest(ctx -> test(i)).as<alltype>();
        tmp.name = k;
        ans.push_back(tmp);
    }
    for(int i = ctx -> test().size();i < ctx ->tfpdef().size();++ i)
    {
        k = visitTfpdef(ctx -> tfpdef(i)).as<std::string>();
        tmp.name = k;
        ans.push_back(tmp);
    }
    return ans;*/
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx)//
{
    //return ctx -> NAME() ->toString();
    return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx)//
{
    if(ctx -> simple_stmt() != nullptr)return visitSimple_stmt(ctx -> simple_stmt());
    if(ctx -> compound_stmt() != nullptr)return visitCompound_stmt(ctx -> compound_stmt());
}

antlrcpp::Any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx)//
{
    return visitSmall_stmt(ctx -> small_stmt());
}

antlrcpp::Any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx)//
{
    if(ctx -> expr_stmt() != nullptr)return visitExpr_stmt(ctx -> expr_stmt());
    if(ctx -> flow_stmt() != nullptr)return visitFlow_stmt(ctx -> flow_stmt());
}

antlrcpp::Any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx)//
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
                    /*if(maps.empty())*/values[a[i].name] = values[a[i].name] + b[i];
                    //else maps.top()[a[i].name] = maps.top()[a[i].name] + b[i];
                    break;
                case 1:
                    /*if(maps.empty())*/values[a[i].name] = values[a[i].name] - b[i];
                    //else maps.top()[a[i].name] = maps.top()[a[i].name] - b[i];
                    break;
                case 2:
                    /*if(maps.empty())*/values[a[i].name] = values[a[i].name] * b[i];
                    //else maps.top()[a[i].name] = maps.top()[a[i].name] * b[i];
                    break;
                case 3:
                    /*if(maps.empty())*/ values[a[i].name] = (double)values[a[i].name] / (double)b[i];
                    //else maps.top()[a[i].name] = (double)maps.top()[a[i].name] / (double)b[i];
                    break;
                case 4:
                    /*if(maps.empty())
                    {*/
                        values[a[i].name] = values[a[i].name] / b[i];
                        if(a[i].now == 2)
                        {
                            a[i].now = 0;
                            a[i].type0 = (integer)a[i].type2;
                            a[i].type2 = NULL;
                        }
                    //}
                    /*else
                    {
                        maps.top()[a[i].name] = maps.top()[a[i].name] / b[i];
                        if(a[i].now == 2)
                        {
                            a[i].now = 0;
                            a[i].type0 = (integer)a[i].type2;
                            a[i].type2 = NULL;
                        }
                    }*/
                    break;
                case 5:
                    /*if(maps.empty())*/values[a[i].name] = values[a[i].name] % b[i];
                    //else maps.top()[a[i].name] = maps.top()[a[i].name] % b[i];
                    break;
            }
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
            for(int j = 0;j < a.size();++ j)
            {
                b[j].name = a[j].name;
                /*if(maps.empty())*/values[a[j].name] = b[j];
                //else maps.top()[a[j].name] = b[j];
            }
        }
        return nullptr;
    }
}

antlrcpp::Any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx)//
{
    if(ctx -> ADD_ASSIGN() != nullptr)return 0;
    if(ctx -> SUB_ASSIGN() != nullptr)return 1;
    if(ctx -> MULT_ASSIGN() != nullptr)return 2;
    if(ctx -> DIV_ASSIGN() != nullptr)return 3;
    if(ctx -> IDIV_ASSIGN() != nullptr)return 4;
    if(ctx -> MOD_ASSIGN() != nullptr)return 5;
}

antlrcpp::Any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx)//
{
    if(ctx -> break_stmt() != nullptr)return visitBreak_stmt(ctx -> break_stmt());
    if(ctx -> continue_stmt() != nullptr)return visitContinue_stmt(ctx -> continue_stmt());
    if(ctx -> return_stmt() != nullptr)return visitReturn_stmt(ctx -> return_stmt());
}

antlrcpp::Any EvalVisitor::visitBreak_stmt(Python3Parser::Break_stmtContext *ctx)//
{
    if(ctx -> BREAK() != nullptr)
        go[go.size() - 1].upBre = 1;
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx)//
{
    if(ctx -> CONTINUE() != nullptr)
        go[go.size() - 1].upCon = 1;
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx)//
{
    if(ctx -> RETURN() != nullptr)
        go[go.size() - 1].upRet = 1;
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx)//
{
    if(ctx -> while_stmt() != nullptr)return visitWhile_stmt(ctx -> while_stmt());
    if(ctx -> if_stmt() != nullptr)return visitIf_stmt(ctx -> if_stmt());
    if(ctx -> funcdef() != nullptr)return visitFuncdef(ctx -> funcdef());
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx)//
{
    ConBreRet mm;
    mm.NOW = ctx -> IF();
    go.push_back(mm);
    for(int i = 0;i < ctx -> test().size();++ i)
    {
        if(visitTest(ctx -> test()[i]).as<alltype>().type1)
        {
            visitSuite(ctx -> suite()[i]);
            go.pop_back();
            return nullptr;
        }
    }
    if(ctx -> ELSE() != nullptr)
    {
        visitSuite(ctx -> suite()[ctx -> suite().size() - 1]);
        go.pop_back();
        return nullptr;
    }
    go.pop_back();
}

antlrcpp::Any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx)//
{
    ConBreRet lp(ctx -> WHILE());
    go.push_back(lp);
    alltype j = visitTest(ctx -> test()).as<alltype>();
    while(j.type1)
    {
        visitSuite(ctx -> suite());
        if(go[go.size() - 1].upBre || go[go.size() - 1].upRet) break;
        j = visitTest(ctx -> test()).as<alltype>();
    }
    go.pop_back();
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx)//
{
    if(ctx -> simple_stmt() != nullptr)return visitSimple_stmt(ctx -> simple_stmt());
    std::vector<alltype> ans;
    antlrcpp::Any tmp;
    for(int i = 0;i < ctx -> stmt().size();++ i)
    {
        //if(visitStmt(ctx -> stmt(i)).is<alltype>())
            tmp = visitStmt(ctx -> stmt(i));
            //for(int j = 0;j < tmp.size();++ j)
              //  ans.push_back(tmp[j]);
        //else visitStmt(ctx -> stmt(i));
        if(go[go.size() - 1].upBre || go[go.size() - 1].upCon || go[go.size() - 1].upRet)break;
    }
    //return ans;
    return nullptr;
}

antlrcpp::Any EvalVisitor::visitTest(Python3Parser::TestContext *ctx)//
{
    return visitOr_test(ctx -> or_test());
}

antlrcpp::Any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx)//
{
    if(ctx -> and_test().size() == 1)return visitAnd_test(ctx -> and_test(0));
    alltype ans = visitAnd_test(ctx -> and_test(0)).as<alltype>();
    ans.now = 1;
    for(int i = 0;i < ctx -> OR().size();++ i)
    {
        if(ans.type1)break;
        ans.type1 = ans || visitAnd_test(ctx -> and_test(i)).as<alltype>();
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx)//
{
    if(ctx -> not_test().size() == 1)return visitNot_test(ctx -> not_test(0));
    alltype ans = visitNot_test(ctx -> not_test(0)).as<alltype>();
    ans.now = 1;
    for(int i = 0;i < ctx -> AND().size();++ i)
    {
        if(!ans.type1)break;
        ans.type1 = ans && visitNot_test(ctx -> not_test(i)).as<alltype>();
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx)//
{
    if(ctx -> not_test() == nullptr) return visitComparison(ctx->comparison());
    alltype ans;
    ans.now = 1;
    ans.type1 = !visitNot_test(ctx -> not_test()).as<alltype>();
    return ans;
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx)//
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

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext *ctx)//
{
    if(ctx -> LESS_THAN() != nullptr) return 0;
    if(ctx -> GREATER_THAN() != nullptr) return 1;
    if(ctx -> EQUALS() != nullptr) return 2;
    if(ctx -> GT_EQ() != nullptr) return 3;
    if(ctx -> LT_EQ() != nullptr) return 4;
    if(ctx -> NOT_EQ_2() != nullptr) return 5;
}

antlrcpp::Any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx)//
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

antlrcpp::Any EvalVisitor::visitAddminus(Python3Parser::AddminusContext *ctx)//
{
    if(ctx -> ADD() != nullptr)return 1;
    if(ctx -> MINUS() != nullptr)return 0;
}

antlrcpp::Any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx)//
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
                ans.type2 = ans.type2;
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

antlrcpp::Any EvalVisitor::visitMuldivmod(Python3Parser::MuldivmodContext *ctx)//
{
    if(ctx -> STAR() != nullptr)return 0;
    if(ctx -> DIV() != nullptr)return 1;
    if(ctx -> IDIV() != nullptr)return 2;
    if(ctx -> MOD() != nullptr)return 3;
}

antlrcpp::Any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx)//
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

antlrcpp::Any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx)//
{
    if(ctx -> trailer() == nullptr)return visitAtom(ctx -> atom());
    else
    {
        alltype tmp;
        tmp = visitAtom(ctx -> atom()).as<alltype>();
        std::vector<alltype> out;
        if(ctx -> atom() -> NAME() -> toString() == "print")
        {
            //nowf = 1;
            out = visitTrailer(ctx -> trailer()).as<std::vector<alltype>>();
            for(int i = 0;i < out.size();++ i)
            {
                if(out[i].now == -1) std::cout<<"None";
                else if(out[i].name == "")print(out[i]);
                else print(values[out[i].name]);
                if(i != out.size() - 1)std::cout<<" ";
            }
            std::cout<<std::endl;
            //nowf = 0;
            return visitAtom(ctx -> atom());
        }
        if(ctx -> atom() -> NAME() -> toString() == "int")
        {
            //nowf = 1;
            out = visitTrailer(ctx -> trailer()).as<std::vector<alltype>>();
            alltype ans;
            alltype tmp = out[0];
            ans.now = 0;
            int op = tmp.now;
            switch(op)
            {
                case 1:
                    if(tmp.type1) ans.type0 = (integer)1;
                    else ans.type0 = (integer)0;
                    break;
                case 2:
                    ans.type0 = (integer)((int)tmp.type2);
                    break;
            }
            //nowf = 0;
            return ans;
        }
        if(ctx -> atom() -> NAME() -> toString() == "float")
        {
            //nowf = 1;
            out = visitTrailer(ctx -> trailer()).as<std::vector<alltype>>();
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
            //nowf = 0;
            return ans;
        }
        if(ctx -> atom() -> NAME() -> toString() == "str")
        {
            //nowf = 1;
            out = visitTrailer(ctx -> trailer()).as<std::vector<alltype>>();
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
            //nowf = 0;
            return ans;
        }
        if(ctx -> atom() -> NAME() -> toString() == "bool")
        {
            //nowf = 1;
            out = visitTrailer(ctx -> trailer()).as<std::vector<alltype>>();
            alltype ans;
            alltype tmp = out[0];
            ans.now = 1;
            if(tmp)ans.type1 = 1;
            else ans.type1 = 0;
            //nowf = 0;
            return ans;
        }
        /*std::string ffn = ctx -> atom() -> NAME() -> toString();
        std::map<std::string,alltype> ftmp;
        nowfunc = fmap[ffn];
        for(int i = 0;i < nowfunc.ftypelist.size();++ i)
            ftmp.insert(std::pair<std::string,alltype>(nowfunc.ftypelist[i].name,nowfunc.ftypelist[i]));
        maps.push(ftmp);
        ConBreRet ftt(ctx -> atom() -> NAME());
        go.push_back(ftt);
        visitSuite(fmap[ffn].fsuite);
        go.pop_back();
        maps.pop();*/
    }
    return visitAtom(ctx -> atom());
}

antlrcpp::Any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx)//
{
    if(ctx -> arglist() != nullptr)return visitArglist(ctx -> arglist());
    else return nullptr;
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx)//
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
        //if(maps.empty())
        //{
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
        //}
        /*else
        {
            if(maps.top().find(ans.name) == maps.top().end())
            {
                maps.top().insert(std::pair<std::string,alltype>(ans.name,ans));
                return ans;
            }
            else
            {
                ans = maps.top()[ans.name];
                return ans;
            }
        }*/
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

antlrcpp::Any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx)//
{
    std::vector<alltype> ans;
    int n = ctx -> test().size();
    antlrcpp::Any nn;
    for(int i = 0 ; i < n ; ++ i)
    {
        nn = visitTest(ctx -> test(i));
        //if(nn.is<alltype>())
            ans.push_back(nn.as<alltype>());
        /*else if(nn.is<std::vector<alltype> >())
            for(int j = 0;j < nn.as<std::vector<alltype> >().size();++ j)
                ans.push_back(nn.as<std::vector<alltype> >()[j]);*/
    }
    return ans;
}

antlrcpp::Any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx)//
{
    //if(maps.empty() || nowf)
    //{
        std::vector<alltype> ans;
        for(int i = 0;i < ctx -> argument().size();++ i)
            ans.push_back(visitArgument(ctx -> argument(i)).as<alltype>());
        return ans;
    //}
    /*for(int i = 0;i < ctx -> argument().size();++ i)
    {
        if(visitArgument(ctx -> argument(i)).is<alltype>())
            maps.top()[nowfunc.ftypelist[i].name] = visitArgument(ctx -> argument(i)).as<alltype>();
    }
    return nullptr;*/
}

antlrcpp::Any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx)//
{
    if(ctx -> NAME() == nullptr)return visitTest(ctx -> test());
    /*else if(!nowf)
    {
        std::string k = ctx -> NAME() -> toString();
        maps.top()[k] = visitTest(ctx -> test()).as<alltype>();
        return nullptr;
    }
     else if(nowf)
     {
        std::string k = ctx -> NAME() -> toString();
        values[k] = visitTest(ctx -> test()).as<alltype>();
        return nullptr;
     }
     */
    else
    {
        if(values.find(ctx -> NAME() -> toString()) == values.end())
        {
            alltype tmp;
            tmp = visitTest(ctx -> test()).as<alltype>();
            tmp.name = ctx -> NAME() -> toString();
            values.insert(std::pair<std::string,alltype>(tmp.name,tmp));
            return tmp;
        }
        else
        {
            alltype tmp;
            tmp = visitTest(ctx -> test()).as<alltype>();
            tmp.name = ctx -> NAME() -> toString();
            values[ctx -> NAME() -> toString()] = tmp;
            return tmp;
        }

    }
}