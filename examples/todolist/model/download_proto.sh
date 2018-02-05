mkdir todolist
cd todolist
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/attributes.proto -o attributes.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/changes.proto -o changes.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/identifiers.proto -o identifiers.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/model.proto -o model.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/validation_rules.proto -o validation_rules.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/values.proto -o values.proto
mkdir c
cd c
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/c/commands.proto -o commands.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/c/enrichments.proto -o enrichments.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/c/events.proto -o events.proto
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/c/rejections.proto -o rejections.proto
cd ..
mkdir q
cd q
curl -s https://raw.githubusercontent.com/SpineEventEngine/todo-list/master/model/src/main/proto/todolist/q/projections.proto -o projections.proto
cd ../.. 