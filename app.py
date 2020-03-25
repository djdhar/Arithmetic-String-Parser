from flask import Flask, request, send_from_directory, render_template
import subprocess,json,os,html

app = Flask(__name__)

@app.errorhandler(404)
def entry_point(e):
    expression = request.args.get("exp")
    if expression is not None:
        expression = bytes(html.unescape(expression), 'utf-8')+b'\n'
        os.system("chmod +x ./processor/a.out")
        three_address = subprocess.check_output("./processor/a.out", input=expression)
        three_address = str(three_address,'utf-8')
        try:
            json_tree = json.loads(subprocess.check_output("python treeToJson.py", shell=True))
        except:            
            json_tree = {"text": {"data":"Invalid Expression"}}
    else:
        three_address = "Enter valid expression"
        json_tree = {"text": {"data":"Please enter the Expression"}}
    return render_template('index.html', address=three_address,tree=json_tree)

@app.route('/assets/<path:path>')
def send_assets(path):
    return send_from_directory('public', path)

if __name__ == '__main__':
    app.run(debug=True)
