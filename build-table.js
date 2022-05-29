let btnAdd = document.querySelector('button');
let table = document.querySelector('table');

let nameInput = document.querySelector('#name');
let ageInput = document.querySelector('#age');
let countryInput = document.querySelector('#country');

function addPerson(name, age, country)
{
    Module.ccall ('addPerson',
                   null,
                   ['string'],
                   ["Nowmi", "25", "USA"]);
}

btnAdd.addEventListener('click', () => {
    let name = nameInput.value;
    let age = ageInput.value;
    let country = countryInput.value;

    addPerson('Nowmi', '25', 'USA');

    let template =
                `<tr>
                    <td>${name}</td>
                    <td>${age}</td>
                    <td>${country}</td>
                </tr>`;

    table.innerHTML += template;
});

// Compiled and ran like so:
// emcc -o table.html table.cpp --shell-file build-table.html -sNO_EXIT_RUNTIME=1 -sEXPORTED_FUNCTIONS=_addPerson -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --emrun
// emrun table.html