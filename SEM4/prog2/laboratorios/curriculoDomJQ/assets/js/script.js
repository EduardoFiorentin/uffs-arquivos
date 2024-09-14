// A) Usando Jquery, inclua um elemento HTML qualquer na tabela já existente na página
let table = $("#table tr:nth-child(2)")
let new_element = $(`<tr class='info_items'><td class='info_item info_name'>Idade</td><td class='info_item'>${(new Date()).getFullYear() - 2004}</td></tr>`)
table.before(new_element)


// B) Usando DOM, busque um elemento da página pelo ID, e altere a propriedade background color para uma nova cor.
let bg_color = $(".skills_item").css("background-color", "#f8e3e3")


// C) Usando jQuery, inclua um elemento li na lista já existente na página;
let new_item = $("<li><p class='objectives_item item'>Desenvolvedor Full Stack</p></li>")
let list = $("#objectives_list")
list.append(new_item)


// D) Usando jQuery, altere o conteúdo de ao menos um parágrafo do currículo;
let ocupation = "Desenvolvedor Front End"
$("#ocupation").html(ocupation)


// E) Usando jQuery inclua dois botões com nomes sugestivos para Aumentar/Diminuir o 
// tamanho da fonte do currículo. Estes botões devem aumentar/diminuir em 2 px a 
// cada clique. O evento deve influenciar na alteração de ao menos um campo com o 
// aumento e diminuição do tamanho da fonte.  

let buttons_container = $("#font-buttons")
let font_target = $("#soft_skills")
let size = parseInt(font_target.css("font-size").replace("px", ""))

let button_a = $("<button class='font-button'>Aumentar Fonte</button>")
let button_b = $("<button class='font-button'>Diminuir Fonte</button>")

button_a.click(() => {
    size += 2
    font_target.css("font-size", `${size}px`)
})

button_b.click(() => {
    size -= 2
    font_target.css("font-size", `${size}px`)
})

buttons_container.append(button_a).append(button_b)
