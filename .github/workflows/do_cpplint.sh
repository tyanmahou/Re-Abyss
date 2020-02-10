#!/usr/bin/env bash

file="Re-Abyss/app/*"

filters=(
    "-legal"
    "-whitespace"
    "-runtime/indentation_namespace"
    "-runtime/explicit"
    "-runtime/references"
    "-build/header_guard"
    "-build/include"
    "-build/namespaces"
    "-readability/todo"
    "-readability/namespace"
)

command="cpplint "
first=true
for filter in "${filters[@]}"
do
    if "${first}"; then
        first=false
        command+="--filter="
    else
        command+=","
    fi
    command+="$filter"
done

command+=" --recursive $file"

echo ${command}
${command}