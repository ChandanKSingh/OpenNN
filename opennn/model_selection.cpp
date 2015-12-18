/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.artelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   C L A S S                                                                  */
/*                                                                                                              */ 
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "model_selection.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 

ModelSelection::ModelSelection(void)
    : training_strategy_pointer(NULL)
    , incremental_order_pointer(NULL)
    , golden_section_order_pointer(NULL)
    , simulated_annelaing_order_pointer(NULL)
    , growing_inputs_pointer(NULL)
    , pruning_inputs_pointer(NULL)
    , genetic_algorithm_pointer(NULL)
{
    set_default();
}


// TRAINING STRATEGY CONSTRUCTOR

/// Training strategy constructor. 
/// @param new_training_strategy_pointer Pointer to a training strategy object.

ModelSelection::ModelSelection(TrainingStrategy* new_training_strategy_pointer)
    : training_strategy_pointer(new_training_strategy_pointer)
    , incremental_order_pointer(NULL)
    , golden_section_order_pointer(NULL)
    , simulated_annelaing_order_pointer(NULL)
    , growing_inputs_pointer(NULL)
    , pruning_inputs_pointer(NULL)
    , genetic_algorithm_pointer(NULL)
{
    set_default();
}


// FILE CONSTRUCTOR

/// File constructor. 
/// @param file_name Name of XML model selection file. 

ModelSelection::ModelSelection(const std::string& file_name)
    : training_strategy_pointer(NULL)
    , incremental_order_pointer(NULL)
    , golden_section_order_pointer(NULL)
    , simulated_annelaing_order_pointer(NULL)
    , growing_inputs_pointer(NULL)
    , pruning_inputs_pointer(NULL)
    , genetic_algorithm_pointer(NULL)
{
    load(file_name);
}


// XML CONSTRUCTOR

/// XML constructor. 
/// @param model_selection_document Pointer to a TinyXML document containing the model selection data.

ModelSelection::ModelSelection(const tinyxml2::XMLDocument& model_selection_document)
    : training_strategy_pointer(NULL)
    , incremental_order_pointer(NULL)
    , golden_section_order_pointer(NULL)
    , simulated_annelaing_order_pointer(NULL)
    , growing_inputs_pointer(NULL)
    , pruning_inputs_pointer(NULL)
    , genetic_algorithm_pointer(NULL)
{
    from_XML(model_selection_document);
}


// DESTRUCTOR

/// Destructor. 

ModelSelection::~ModelSelection(void)
{
}


// METHODS

// TrainingStrategy* get_training_strategy_pointer(void) const method

/// Returns a pointer to the training strategy object.

TrainingStrategy* ModelSelection::get_training_strategy_pointer(void) const
{
#ifdef __OPENNN_DEBUG__

    if(!training_strategy_pointer)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "TrainingStrategy* get_training_strategy_pointer(void) const method.\n"
               << "Training strategy pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }

#endif

    return(training_strategy_pointer);
}

// bool has_training_strategy(void) const method

/// Returns true if this model selection has a training strategy associated,
/// and false otherwise.

bool ModelSelection::has_training_strategy(void) const
{
    if(training_strategy_pointer)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

// const OrderSelectionType& get_order_selection_type(void) const method

/// Returns the type of algorithm for the order selection.

const ModelSelection::OrderSelectionType& ModelSelection::get_order_selection_type(void) const
{
    return(order_selection_type);
}

// const InputSelectionType& get_inputs_selection_type(void) const method

/// Returns the type of algorithm for the inputs selection.

const ModelSelection::InputsSelectionType& ModelSelection::get_inputs_selection_type(void) const
{
    return(inputs_selection_type);
}


// IncrementalOrder* get_incremental_order_pointer(void) const method

/// Returns a pointer to the incremental order selection algorithm.

IncrementalOrder* ModelSelection::get_incremental_order_pointer(void) const
{
    return(incremental_order_pointer);
}

// GoldenSectionOrder* get_golden_section_order_pointer(void) const method

/// Returns a pointer to the golden section order selection algorithm.

GoldenSectionOrder* ModelSelection::get_golden_section_order_pointer(void) const
{
    return(golden_section_order_pointer);
}

// SimulatedAnnealingOrder* get_simulated_annealing_order_pointer(void) const method

/// Returns a pointer to the simulated annealing order selection algorithm.

SimulatedAnnealingOrder* ModelSelection::get_simulated_annealing_order_pointer(void) const
{
    return(simulated_annelaing_order_pointer);
}

// GrowingInputs* get_growing_inputs_pointer(void) const method

/// Returns a pointer to the growing inputs selection algorithm.

GrowingInputs* ModelSelection::get_growing_inputs_pointer(void) const
{
    return(growing_inputs_pointer);
}

// PruningInputs* get_pruning_inputs_pointer(void) const method

/// Returns a pointer to the pruning inputs selection algorithm.

PruningInputs* ModelSelection::get_pruning_inputs_pointer(void) const
{
    return(pruning_inputs_pointer);
}

// GeneticAlgorithm* get_genetic_algorithm_pointer(void) const method

/// Returns a pointer to the genetic inputs selection algorithm.

GeneticAlgorithm* ModelSelection::get_genetic_algorithm_pointer(void) const
{
    return(genetic_algorithm_pointer);
}

// void set_default(void) method

/// Sets the members of the model selection object to their default values.

void ModelSelection::set_default(void)
{
    set_order_selection_type(ModelSelection::INCREMENTAL_SELECTION);
    set_inputs_selection_type(ModelSelection::GROWING_SELECTION);
}

// void set_order_selection_type(const OrderSelectionType&) method

/// Sets a new method for selecting the order which have more impact on the targets.
/// @param new_order_selection_type Method for selecting the order (NO_ORDER_SELECTION, INCREMENTAL_SELECTION, GOLDEN_SECTION, SIMULATED_ANNEALING).

void ModelSelection::set_order_selection_type(const ModelSelection::OrderSelectionType& new_order_selection_type)
{
    destruct_order_selection();

    order_selection_type = new_order_selection_type;

    switch (new_order_selection_type)
    {
    case NO_ORDER_SELECTION:
    {
        // do nothing

        break;
    }
    case INCREMENTAL_SELECTION:
    {
        incremental_order_pointer = new IncrementalOrder(training_strategy_pointer);

        break;
    }
    case GOLDEN_SECTION:
    {
        golden_section_order_pointer = new GoldenSectionOrder(training_strategy_pointer);

        break;
    }
    case SIMULATED_ANNEALING:
    {
        simulated_annelaing_order_pointer = new SimulatedAnnealingOrder(training_strategy_pointer);

        break;
    }
    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void set_order_selection_method(const OrderSelectionType&) const method.\n"
               << "Unknow order selection method.\n";

        throw std::logic_error(buffer.str());

        break;
    }
    }


}

// void set_order_selection_type(const std::string&) method

/// Sets a new order selection algorithm from a string.
/// @param new_order_selection_type String with the order selection type.

void ModelSelection::set_order_selection_type(const std::string& new_order_selection_type)
{
    if(new_order_selection_type == "NO_ORDER_SELECTION")
    {
        set_order_selection_type(NO_ORDER_SELECTION);
    }
    else if(new_order_selection_type == "INCREMENTAL_SELECTION")
    {
        set_order_selection_type(INCREMENTAL_SELECTION);
    }
    else if(new_order_selection_type == "GOLDEN_SECTION")
    {
        set_order_selection_type(GOLDEN_SECTION);
    }
    else if(new_order_selection_type == "SIMULATED_ANNEALING")
    {
        set_order_selection_type(SIMULATED_ANNEALING);
    }
    else
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void set_order_selection_type(const std::string&) method.\n"
               << "Unknown order selection type: " << new_order_selection_type << ".\n";

        throw std::logic_error(buffer.str());
    }
}

// void set_inputs_selection_type(const InputSelectionType&) method

/// Sets a new method for selecting the inputs which have more impact on the targets.
/// @param new_inputs_selection_type Method for selecting the inputs (NO_INPUT_SELECTION, GROWING_SELECTION, PRUNING_SELECTION, GENETIC_SELECTION).

void ModelSelection::set_inputs_selection_type(const ModelSelection::InputsSelectionType& new_inputs_selection_type)
{
    destruct_inputs_selection();

    inputs_selection_type = new_inputs_selection_type;

    switch (new_inputs_selection_type)
    {
    case NO_INPUT_SELECTION:
    {
        // do nothing

        break;
    }
    case GROWING_SELECTION:
    {
        growing_inputs_pointer = new GrowingInputs(training_strategy_pointer);

        break;
    }
    case PRUNING_SELECTION:
    {
        pruning_inputs_pointer = new PruningInputs(training_strategy_pointer);

        break;
    }
    case GENETIC_SELECTION:
    {
        genetic_algorithm_pointer = new GeneticAlgorithm(training_strategy_pointer);

        break;
    }
    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void set_inputs_selection_method(const InputsSelectionType&) const method.\n"
               << "Unknow inputs selection method.\n";

        throw std::logic_error(buffer.str());

        break;
    }
    }
}

// void set_inputs_selection_type(const std::string&) method

/// Sets a new inputs selection algorithm from a string.
/// @param new_inputs_selection_type String with the inputs selection type.

void ModelSelection::set_inputs_selection_type(const std::string& new_inputs_selection_type)
{
    if(new_inputs_selection_type == "NO_INPUT_SELECTION")
    {
        set_inputs_selection_type(NO_INPUT_SELECTION);
    }
    else if(new_inputs_selection_type == "GROWING_SELECTION")
    {
        set_inputs_selection_type(GROWING_SELECTION);
    }
    else if(new_inputs_selection_type == "PRUNING_SELECTION")
    {
        set_inputs_selection_type(PRUNING_SELECTION);
    }
    else if(new_inputs_selection_type == "GENETIC_SELECTION")
    {
        set_inputs_selection_type(GENETIC_SELECTION);
    }
    else
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void set_inputs_selection_type(const std::string&) method.\n"
               << "Unknown inputs selection type: " << new_inputs_selection_type << ".\n";

        throw std::logic_error(buffer.str());
    }
}

// void set_training_strategy_pointer(TrainingStrategy*) method

/// Sets a new training strategy pointer.
/// @param new_training_strategy_pointer Pointer to a training strategy object.

void ModelSelection::set_training_strategy_pointer(TrainingStrategy* new_training_strategy_pointer)
{
    training_strategy_pointer = new_training_strategy_pointer;

    switch(order_selection_type)
    {
    case NO_ORDER_SELECTION:
    {
        // do nothing

        break;
    }
    case INCREMENTAL_SELECTION:
    {
        incremental_order_pointer->set_training_strategy_pointer(new_training_strategy_pointer);
        break;
    }
    case GOLDEN_SECTION:
    {
        golden_section_order_pointer->set_training_strategy_pointer(new_training_strategy_pointer);
        break;
    }
    case SIMULATED_ANNEALING:
    {
        simulated_annelaing_order_pointer->set_training_strategy_pointer(new_training_strategy_pointer);
        break;
    }
    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void set_training_strategy_pointer(TrainingStrategy*) method.\n"
               << "Unknown order selection type.\n";

        throw std::logic_error(buffer.str());
    }
    }

    switch(inputs_selection_type)
    {
    case NO_ORDER_SELECTION:
    {
        // do nothing

        break;
    }
    case GROWING_SELECTION:
    {
        growing_inputs_pointer->set_training_strategy_pointer(new_training_strategy_pointer);
        break;
    }
    case PRUNING_SELECTION:
    {
        pruning_inputs_pointer->set_training_strategy_pointer(new_training_strategy_pointer);
        break;
    }
    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void set_training_strategy_pointer(TrainingStrategy*) method.\n"
               << "Unknown inputs selection type.\n";

        throw std::logic_error(buffer.str());
    }
    }
}

// void destruct_order_selection(void) method

/// This method deletes the order selection algorithm object which composes this model selection object.

void ModelSelection::destruct_order_selection(void)
{
    delete incremental_order_pointer;
    delete golden_section_order_pointer;
    delete simulated_annelaing_order_pointer;

    incremental_order_pointer = NULL;
    golden_section_order_pointer = NULL;
    simulated_annelaing_order_pointer = NULL;

    order_selection_type = NO_ORDER_SELECTION;
}

// void destruct_inputs_selection(void) method

/// This method deletes the inputs selection algorithm object which composes this model selection object.

void ModelSelection::destruct_inputs_selection(void)
{
    delete growing_inputs_pointer;
    delete pruning_inputs_pointer;
    delete genetic_algorithm_pointer;

    growing_inputs_pointer = NULL;
    pruning_inputs_pointer = NULL;
    genetic_algorithm_pointer = NULL;

    inputs_selection_type = NO_INPUT_SELECTION;
}


// void check(void) const method

/// Checks that the different pointers needed for performing the model selection are not NULL.

void ModelSelection::check(void) const
{

    // Training algorithm stuff

    std::ostringstream buffer;

    if(!training_strategy_pointer)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Pointer to training strategy is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Performance functional stuff

    const PerformanceFunctional* performance_functional_pointer = training_strategy_pointer->get_performance_functional_pointer();

    if(!performance_functional_pointer)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Pointer to performance functional is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Neural network stuff

    const NeuralNetwork* neural_network_pointer = performance_functional_pointer->get_neural_network_pointer();

    if(!neural_network_pointer)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Pointer to neural network is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

    if(!multilayer_perceptron_pointer)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Pointer to multilayer perceptron is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    if(multilayer_perceptron_pointer->is_empty())
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Multilayer Perceptron is empty.\n";

        throw std::logic_error(buffer.str());
    }

    // Data set stuff

    const DataSet* data_set_pointer = performance_functional_pointer->get_data_set_pointer();

    if(!data_set_pointer)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Pointer to data set is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    const Instances& instances = data_set_pointer->get_instances();

    const size_t generalization_instances_number = instances.count_generalization_instances_number();

    if(generalization_instances_number == 0)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void check(void) const method.\n"
               << "Number of generalization instances is zero.\n";

        throw std::logic_error(buffer.str());
    }

}

// ModelSelectionResults perform_order_selection(void) method

/// Perform the order selection, returns a structure with the results of the order selection
/// It also set the neural network of the training strategy pointer with the optimum parameters

ModelSelection::ModelSelectionResults ModelSelection::perform_order_selection(void) const
{
#ifdef __OPENNN_DEBUG__

    std::ostringstream buffer;

    if(order_selection_type == NO_ORDER_SELECTION)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "ModelSelectionResults perform_order_selection(void) const method.\n"
               << "None order selection term is used.\n";

        throw std::logic_error(buffer.str());
    }

    check();

#endif

    ModelSelectionResults results;

    switch(order_selection_type)
    {
    case INCREMENTAL_SELECTION:
    {
        results.incremental_order_results_pointer = incremental_order_pointer->perform_order_selection();
        break;
    }
    case GOLDEN_SECTION:
    {
        results.golden_section_order_results_pointer = golden_section_order_pointer->perform_order_selection();
        break;
    }
    case SIMULATED_ANNEALING:
    {
        results.simulated_annealing_order_results_pointer = simulated_annelaing_order_pointer->perform_order_selection();
        break;
    }
    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "ModelSelectionResults perform_order_selection(void) method.\n"
               << "Unknown order selection method.\n";

        throw std::logic_error(buffer.str());

        break;
    }
    }

    return(results);
}

// ModelSelectionResults perform_inputs_selection(void) method

/// Perform the inputs selection, returns a structure with the results of the inputs selection.
/// It also set the neural network of the training strategy pointer with the optimum parameters.

ModelSelection::ModelSelectionResults ModelSelection::perform_inputs_selection(void) const
{
#ifdef __OPENNN_DEBUG__

    std::ostringstream buffer;

    if(inputs_selection_type == NO_INPUT_SELECTION)
    {
        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "ModelSelectionResults perform_inputs_selection(void) const method.\n"
               << "None inputs selection term is used.\n";

        throw std::logic_error(buffer.str());
    }

    check();

#endif

    ModelSelectionResults results;

    switch(inputs_selection_type)
    {
    case GROWING_SELECTION:
    {
        results.growing_inputs_results_pointer = growing_inputs_pointer->perform_inputs_selection();
        break;
    }
    case PRUNING_SELECTION:
    {
        results.pruning_inputs_results_pointer = pruning_inputs_pointer->perform_inputs_selection();
        break;
    }
    case GENETIC_SELECTION:
    {
        results.genetic_algorithm_results_pointer = genetic_algorithm_pointer->perform_inputs_selection();
        break;
    }
    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "ModelSelectionResults perform_inputs_selection(void) method.\n"
               << "Unknown inputs selection method.\n";

        throw std::logic_error(buffer.str());

        break;
    }
    }

    return(results);
}

// ModelSelectionResults perform_model_selection(void) const method

/// @todo
/// Perform inputs selection and order selection.

ModelSelection::ModelSelectionResults ModelSelection::perform_model_selection(void) const
{
    ModelSelectionResults model_selection_results;

    model_selection_results = perform_order_selection();

    return(model_selection_results);
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the model selection object into a XML document of the TinyXML library. 
/// See the OpenNN manual for more information about the format of this document. 

tinyxml2::XMLDocument* ModelSelection::to_XML(void) const
{
    std::ostringstream buffer;

    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

    // Training strategy

    tinyxml2::XMLElement* model_selection_element = document->NewElement("ModelSelection");

    document->InsertFirstChild(model_selection_element);

    // Order Selection

    switch(order_selection_type)
    {
    case NO_ORDER_SELECTION:
    {
        tinyxml2::XMLElement* order_selection_element = document->NewElement("OrderSelection");
        model_selection_element->LinkEndChild(order_selection_element);

        order_selection_element->SetAttribute("Type", "NO_ORDER_SELECTION");
    }
        break;

    case INCREMENTAL_SELECTION:
    {
        tinyxml2::XMLElement* order_selection_element = document->NewElement("OrderSelection");
        model_selection_element->LinkEndChild(order_selection_element);

        order_selection_element->SetAttribute("Type", "INCREMENTAL_SELECTION");

        const tinyxml2::XMLDocument* incremental_order_document = incremental_order_pointer->to_XML();

        const tinyxml2::XMLElement* incremental_order_element = incremental_order_document->FirstChildElement("IncrementalOrder");

        DeepClone(order_selection_element, incremental_order_element, document, NULL);

        delete incremental_order_document;
    }
        break;

    case GOLDEN_SECTION:
    {
        tinyxml2::XMLElement* order_selection_element = document->NewElement("OrderSelection");
        model_selection_element->LinkEndChild(order_selection_element);

        order_selection_element->SetAttribute("Type", "GOLDEN_SECTION");

        const tinyxml2::XMLDocument* golden_section_order_document = golden_section_order_pointer->to_XML();

        const tinyxml2::XMLElement* golden_section_order_element = golden_section_order_document->FirstChildElement("GoldenSectionOrder");

        DeepClone(order_selection_element, golden_section_order_element, document, NULL);

        delete golden_section_order_document;
    }
        break;

    case SIMULATED_ANNEALING:
    {
        tinyxml2::XMLElement* order_selection_element = document->NewElement("OrderSelection");
        model_selection_element->LinkEndChild(order_selection_element);

        order_selection_element->SetAttribute("Type", "SIMULATED_ANNEALING");

        const tinyxml2::XMLDocument* simulated_annealing_order_document = simulated_annelaing_order_pointer->to_XML();

        const tinyxml2::XMLElement* simulated_annealing_order_element = simulated_annealing_order_document->FirstChildElement("SimulatedAnnealingOrder");

        DeepClone(order_selection_element, simulated_annealing_order_element, document, NULL);

        delete simulated_annealing_order_document;
    }
        break;

    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "tinyxml2::XMLDocument* to_XML(void) const method.\n"
               << "Unknown order selection type.\n";

        throw std::logic_error(buffer.str());
    }
        break;
    }

    // Inputs Selection

    switch(inputs_selection_type)
    {
    case NO_INPUT_SELECTION:
    {
        tinyxml2::XMLElement* inputs_selection_element = document->NewElement("InputsSelection");
        model_selection_element->LinkEndChild(inputs_selection_element);

        inputs_selection_element->SetAttribute("Type", "NO_INPUT_SELECTION");
    }
        break;

    case GROWING_SELECTION:
    {
        tinyxml2::XMLElement* inputs_selection_element = document->NewElement("InputsSelection");
        model_selection_element->LinkEndChild(inputs_selection_element);

        inputs_selection_element->SetAttribute("Type", "GROWING_SELECTION");

        const tinyxml2::XMLDocument* growing_inputs_document = growing_inputs_pointer->to_XML();

        const tinyxml2::XMLElement* growing_inputs_element = growing_inputs_document->FirstChildElement("GrowingInputs");

        DeepClone(inputs_selection_element, growing_inputs_element, document, NULL);

        delete growing_inputs_document;
    }
        break;

    case PRUNING_SELECTION:
    {
        tinyxml2::XMLElement* inputs_selection_element = document->NewElement("InputsSelection");
        model_selection_element->LinkEndChild(inputs_selection_element);

        inputs_selection_element->SetAttribute("Type", "PRUNING_SELECTION");

        const tinyxml2::XMLDocument* pruning_inputs_document = pruning_inputs_pointer->to_XML();

        const tinyxml2::XMLElement* pruning_inputs_element = pruning_inputs_document->FirstChildElement("PruningInputs");

        DeepClone(inputs_selection_element, pruning_inputs_element, document, NULL);

        delete pruning_inputs_document;
    }
        break;

    case GENETIC_SELECTION:
    {
        tinyxml2::XMLElement* inputs_selection_element = document->NewElement("InputsSelection");
        model_selection_element->LinkEndChild(inputs_selection_element);

        inputs_selection_element->SetAttribute("Type", "GENETIC_SELECTION");

        const tinyxml2::XMLDocument* genetic_algorithm_document = genetic_algorithm_pointer->to_XML();

        const tinyxml2::XMLElement* genetic_algorithm_element = genetic_algorithm_document->FirstChildElement("GeneticAlgorithm");

        DeepClone(inputs_selection_element, genetic_algorithm_element, document, NULL);

        delete genetic_algorithm_document;
    }
        break;

    default:
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "tinyxml2::XMLDocument* to_XML(void) const method.\n"
               << "Unknown inputs selection type.\n";

        throw std::logic_error(buffer.str());
    }
        break;
    }

    return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Loads the members of this model selection object from a XML document.
/// @param document XML document of the TinyXML library.

void ModelSelection::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("ModelSelection");

    if(!root_element)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Model Selection element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Order Selection
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("OrderSelection");

        if(element)
        {
            const std::string new_order_selection_type = element->Attribute("Type");

            set_order_selection_type(new_order_selection_type);

            switch(order_selection_type)
            {
            case NO_ORDER_SELECTION:
            {
                // do nothing
            }
                break;
            case INCREMENTAL_SELECTION:
            {
                tinyxml2::XMLDocument new_document;

                tinyxml2::XMLElement* element_clone = new_document.NewElement("IncrementalOrder");
                new_document.InsertFirstChild(element_clone);

                DeepClone(element_clone, element, &new_document, NULL);

                incremental_order_pointer->from_XML(new_document);
            }
                break;
            case GOLDEN_SECTION:
            {
                tinyxml2::XMLDocument new_document;

                tinyxml2::XMLElement* element_clone = new_document.NewElement("GoldenSectionOrder");
                new_document.InsertFirstChild(element_clone);

                DeepClone(element_clone, element, &new_document, NULL);

                golden_section_order_pointer->from_XML(new_document);
            }
                break;
            case SIMULATED_ANNEALING:
            {
                tinyxml2::XMLDocument new_document;

                tinyxml2::XMLElement* element_clone = new_document.NewElement("SimulatedAnnealingOrder");
                new_document.InsertFirstChild(element_clone);

                DeepClone(element_clone, element, &new_document, NULL);

                simulated_annelaing_order_pointer->from_XML(new_document);
            }
                break;
            default:
            {
                std::ostringstream buffer;

                buffer << "OpenNN Exception: ModelSelection class.\n"
                       << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                       << "Unknown order selection type.\n";

                throw std::logic_error(buffer.str());
            }
                break;
            }
        }
    }

    // Inputs Selection
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("InputsSelection");

        if(element)
        {
            const std::string new_inputs_selection_type = element->Attribute("Type");

            set_inputs_selection_type(new_inputs_selection_type);

            switch(inputs_selection_type)
            {
            case NO_INPUT_SELECTION:
            {
                // do nothing
            }
                break;
            case GROWING_SELECTION:
            {
                tinyxml2::XMLDocument new_document;

                tinyxml2::XMLElement* element_clone = new_document.NewElement("GrowingInputs");
                new_document.InsertFirstChild(element_clone);

                DeepClone(element_clone, element, &new_document, NULL);

                growing_inputs_pointer->from_XML(new_document);
            }
                break;
            case PRUNING_SELECTION:
            {
                tinyxml2::XMLDocument new_document;

                tinyxml2::XMLElement* element_clone = new_document.NewElement("PruningInputs");
                new_document.InsertFirstChild(element_clone);

                DeepClone(element_clone, element, &new_document, NULL);

                pruning_inputs_pointer->from_XML(new_document);
            }
                break;
            case GENETIC_SELECTION:
            {
                tinyxml2::XMLDocument new_document;

                tinyxml2::XMLElement* element_clone = new_document.NewElement("GeneticAlgorithm");
                new_document.InsertFirstChild(element_clone);

                DeepClone(element_clone, element, &new_document, NULL);

                genetic_algorithm_pointer->from_XML(new_document);
            }
                break;
            default:
            {
                std::ostringstream buffer;

                buffer << "OpenNN Exception: ModelSelection class.\n"
                       << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
                       << "Unknown inputs selection type.\n";

                throw std::logic_error(buffer.str());
            }
                break;
            }
        }
    }
}


// void print(void) method

/// Prints to the screen the XML representation of this model selection object. 

void ModelSelection::print(void) const
{
    std::cout << to_XML();
}


// void save(const std::string&) const method

/// Saves the model selection members to a XML file. 
/// @param file_name Name of model selection XML file. 

void ModelSelection::save(const std::string& file_name) const
{
    tinyxml2::XMLDocument* document = to_XML();

    document->SaveFile(file_name.c_str());

    delete document;
}


// void load(const std::string&) method

/// Loads the model selection members from a XML file. 
/// @param file_name Name of model selection XML file. 

void ModelSelection::load(const std::string& file_name)
{
    tinyxml2::XMLDocument document;

    if (document.LoadFile(file_name.c_str()))
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: ModelSelection class.\n"
               << "void load(const std::string&) method.\n"
               << "Cannot load XML file " << file_name << ".\n";

        throw std::logic_error(buffer.str());
    }

    from_XML(document);
}

// void ModelSelectionResults::save(const std::string&) const method

/// Saves the results structure to a data file.
/// @param file_name Name of model selection results data file.

void ModelSelection::ModelSelectionResults::save(const std::string& file_name) const
{
    std::ofstream file(file_name.c_str());

    file << "% Model Selection Results\n";

    file << "\n% Order Selection Results\n";

    if (incremental_order_results_pointer)
    {
        file << incremental_order_results_pointer->to_string();
    }

    if (golden_section_order_results_pointer)
    {
        file << golden_section_order_results_pointer->to_string();
    }

    if (simulated_annealing_order_results_pointer)
    {
        file << simulated_annealing_order_results_pointer->to_string();
    }

    file << "\n% Inputs Selection Results\n";

    if (growing_inputs_results_pointer)
    {
        file << growing_inputs_results_pointer->to_string();
    }

    if (pruning_inputs_results_pointer)
    {
        file << pruning_inputs_results_pointer->to_string();
    }

    if (genetic_algorithm_results_pointer)
    {
        file << genetic_algorithm_results_pointer->to_string();
    }

    file.close();
}

}
