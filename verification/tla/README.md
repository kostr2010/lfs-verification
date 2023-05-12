# TLA VERIFICATION

tla model verifies push/pop functions of the stack

it checks the following criteria:

- invariant - only one thread is allowed in the critical zone at a time
- temporal property - stack should be empty at the end of all operations

you can parse `lfs.tla` to obtain tla+ file and congig and then validate this model

I used this extension: https://marketplace.visualstudio.com/items?itemName=alygin.vscode-tlaplus
