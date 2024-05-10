# the purpose of the script is to find all the actions and register it to worker_amac.c
import os
from pprint import pprint

def register_action():
    # get the list of .h files in the current directory
    # get the path of the script
    path = os.path.dirname(os.path.realpath(__file__))
    folder = os.listdir(path)
    # get the list of .h files in the current directory
    header_files = []
    for file in folder:
        if file.endswith(".h"):
            # filter fsm_amac_nf_lib.h and fsm_amac_nf_common.h
            if file != "fsm_amac_nf_lib.h" and file != "fsm_amac_nf_common.h":
                header_files.append(file)
    actions = []
    control_state_init = {}
    for header_file in header_files:
        # open the file
        full_path = os.path.join(path, header_file)
        with open(full_path, "r") as file:
            # read the file
            lines = file.readlines()
            string = "".join(lines)
            # find the actions
            # the format of the action is INLINE_ACTOR_ACTION(action_name)
            import re
            pattern = re.compile(r"INLINE_ACTOR_ACTION\((.*?)\)")
            matches = pattern.findall(string)
            for match in matches:
                actions.append(match)

            # the format of the control state init is ACTOR_CONTROL_STATE_INIT(init_name)
            pattern = re.compile(r"ACTOR_CONTROL_STATE_INIT\((.*?)\)")
            header_file_name = header_file.split(".")[0]
            if header_file_name == "system_action":
                continue
            matches = pattern.findall(string)
            # there should be only one match
            try:
                assert len(matches) == 1
                control_state_init[header_file_name] = matches[0]
            except AssertionError:
                print("header file name: ", header_file_name)
                print("there should be only one match")
                exit(1)

    for i in range(len(actions)):
        # for each action, transform the string into something like {.run = upf_encapsulate, .name = "upf_encapsulate"}
        actions[i] = "{.run = " + actions[i] + ", .name = \"" + actions[i] + "\"}"
        if actions[i] == "Exit":
            actions[i] = "{.run = Exit, .name = \"exit\"}"
    print("number of actions: ", len(actions))
    pprint(",\n".join(actions))





    path = os.path.dirname(os.path.realpath(__file__))
    parent_folder = os.path.dirname(path)
    worker_amac_path = os.path.join(parent_folder, "worker/worker_amac.c")
    # read ../worker/worker_amac.c
    # find the lines that contain
    # struct runtime_actor_table runtimeActorTable[] ={
    #
    # };
    # replace the content inside the curly braces with the actions
    # write the file back
    with open(worker_amac_path, "r") as file:
        lines = file.readlines()
        string = "".join(lines)
        # find the actions
        # the format of the action is INLINE_ACTOR_ACTION(action_name)
        import re
        # match struct runtime_actor_table runtimeActorTable[]
        pattern = re.compile(r"struct runtime_actor_table runtimeActorTable\[\] =\s*{.*?};", re.DOTALL)
        match = pattern.search(string)
        # replace the content inside the curly braces with the actions
        # the result must match the pattern as well
        string = string.replace(match.group(0), "struct runtime_actor_table runtimeActorTable[] = {\n" + ",\n\t".join(actions) + "\n};")
        assert pattern.search(string) is not None

    with open(worker_amac_path, "w") as file:
        file.write(string)


    # update fsm_amac_nf_lib.h
    # format
    #ifndef NFLAMBDA_RUNTIME_FSM_AMAC_NF_LIB_H
    #define NFLAMBDA_RUNTIME_FSM_AMAC_NF_LIB_H
    # ... include header files
    #endif

    fsm_amac_nf_lib_path = os.path.join(parent_folder, "nf/fsm_amac_nf_lib.h")
    # write the file according to the format
    with open(fsm_amac_nf_lib_path, "w") as file:
        file.write("#ifndef NFLAMBDA_RUNTIME_FSM_AMAC_NF_LIB_H\n")
        file.write("#define NFLAMBDA_RUNTIME_FSM_AMAC_NF_LIB_H\n")
        for header_file in header_files:
            file.write("#include \"" + header_file + "\"\n")
        file.write("#endif\n")


    # update struct control_state_table controlStateTable[] in worker_amac.c
    # format
    # struct control_state_table controlStateTable[] = {
    #     {.init = upf_encapsulate_init, .name = "upf_encapsulation"},
    #}

    # read ../worker/worker_amac.c
    # find the lines that contain
    # struct control_state_table controlStateTable[] = {
    #
    # };
    # replace the content inside the curly braces with the actions
    # write the file back
    with open(worker_amac_path, "r") as file:
        lines = file.readlines()
        string = "".join(lines)
        # find the actions
        # the format of the action is INLINE_ACTOR_ACTION(action_name)
        import re
        # match struct runtime_actor_table runtimeActorTable[]
        pattern = re.compile(r"struct control_state_table controlStateTable\[\] =\s*{.*?};", re.DOTALL)
        match = pattern.search(string)
        # replace the content inside the curly braces with the actions
        # the result must match the pattern as well
        temp_string = ""
        for key, value in control_state_init.items():
            print("adding control state init: ", key, value)
            temp_string += "{.init = " + value + ", .name = \"" + key + "\"},\n\t"

        # workaround for the bug #############################################
        temp_string += "{.init = cuckoo_hash_init, .name = \"cuckoo_hash_rtc\"},\n\t"
        temp_string += "{.init = interval_tree_init, .name = \"interval_tree_rtc\"},\n\t"
        ######################################################################
        print("temp string: ", temp_string)
        string = string.replace(match.group(0), "struct control_state_table controlStateTable[] = {\n" + temp_string + "\n};")
        assert pattern.search(string) is not None

    with open(worker_amac_path, "w") as file:
        file.write(string)


def register_control_state():
    # list all the files under control_state directory
    path = os.path.dirname(os.path.realpath(__file__))
    parent_folder = os.path.dirname(path)
    control_state_path = os.path.join(parent_folder, "nf/control_state")
    header_files = os.listdir(control_state_path)
    print("header files: ", header_files)
    # filter the header files that start with control_state
    header_files = [file for file in header_files if file.startswith("controlstate")]
    print("header files: ", header_files)

    # write the header_files into control_state_collection.h to include
    control_state_collection_path = os.path.join(parent_folder, "nf/control_state/control_state_collection.h")
    with open(control_state_collection_path, "w") as file:
        # write include guard
        file.write("#ifndef RUNTIME_CONTROL_STATE_COLLECTION_H\n")
        file.write("#define RUNTIME_CONTROL_STATE_COLLECTION_H\n")
        # write include header files
        for header_file in header_files:
            file.write("#include \"" + header_file + "\"\n")
        # write include guard
        file.write("#endif\n")


# pip install loguru
if __name__ == "__main__":
    register_action()
    register_control_state()

