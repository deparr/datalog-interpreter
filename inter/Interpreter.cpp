#include "Interpreter.h"

void Interpreter::InterpretProgram() {
    // Create empty relations from the list of schemes
    for (Predicate s : *schemes) {
        Relation newRelation(*s);
        for (size_t i = 0; i < s.ListSize(); i++) {
            newRelation.AddToHeader(s.GetParameter(i));
        }
        database->AddRelation(newRelation);
    }

    // Populate the relations from the given facts
    for (Predicate f : *facts) {
        Tuple newTuple;
        for (size_t i = 0; i < f.ListSize(); i++) {
            newTuple.Add(f.GetParameter(i));
        }
        database->MatchAddTuple(*f, newTuple);
    }


	// Evaluate each rule using relational algebra
    bool terminate = false;
    int passes = 0;
    std::cout << "Rule Evaluation\n";
    do {
        terminate = false;
        for (Rule rule : *rules) {

            std::cout << rule;
            Relation* relptr = nullptr;

            // Branch if rule is multi rule
            if (rule.IsMultiRule()) {
                std::vector<Relation*> relptrs;
                for (size_t i = 0; i < rule.Size(); i++) {
                    relptrs.push_back(EvaluatePredicate(rule[i]));
                }


                relptr = relptrs[0];
                for (size_t i = 1; i < relptrs.size(); i++) {
                    relptr = relptr->Join(relptrs[i]);
                }


            }

            // Branch for single rules
            else {
                relptr = EvaluatePredicate(rule[0]);
            }


            // Project columns that appear in head predicate
            std::vector<std::string> headCols;
            for (size_t i = 0; i < rule.GetHeadPred().ListSize(); i++) {
                headCols.push_back(rule.GetHeadPred().GetParameter(i));
            }
            *relptr = relptr->Project(headCols);

    

            // Union with the matching relation in database
            if (relptr->Union(database->GetRelation(*rule.GetHeadPred()))) { terminate = true; }

            // MIGHT NOT NEED THIS, OR IT MIHT NOT EVEN WORK
            // for (Relation* relptr : relptrs) delete relptr;
        }
        passes += 1;
    } while (terminate);

    std::cout << "\nSchemes populated after " << passes << " passes through the Rules.\n\n";
	
    // Evaluate each query using relational operations
    std::cout << "Query Evaluation\n";
    for (Predicate query : *queries) {
        Relation* relptr = EvaluatePredicate(query);
        std::cout << query << "? ";
        if (!relptr->Empty()) {
            std::cout << "Yes(" << relptr->ListSize() << ")\n" << *relptr;
        }
        else {
            std::cout << "No\n";
        }
    }
}

Relation* Interpreter::EvaluatePredicate(const Predicate& pred) {
    Relation* relptr = new Relation();
    *relptr = database->GetRelation(*pred);
    std::map<std::string, size_t> varRecord;

    std::vector<size_t> projCols;	// Columns for projection
    std::vector<std::string> varNames;	// Column Names for final relation
    size_t colIndex = 0;

    // Select constants AND variables
    for (size_t i = 0; i < pred.ListSize(); i++) {
        Parameter p = pred.GetWholeParameter(i);
        if (p.GetType()) {
            *relptr = relptr->Select(i, *p);
        }
        else {
            if (varRecord.count(*p)) {
                *relptr = relptr->Select(i, varRecord[*p]);
            }
            else {
                projCols.push_back(colIndex);
                varNames.push_back(*p);
                varRecord[*p] = i;
            }
        }
	colIndex++;
    }

    // Project on variable columns
    *relptr = relptr->Project(projCols);

    // Rename to match variables in query
    *relptr = relptr->Rename(varNames);

    return relptr;
}
