import flet as ft

def main(page: ft.Page):
    page.title = "Python Workbench"

    # Add controls to the page
    page.add(ft.Text("Hello, user!"))

ft.app(target=main)