from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/data', methods=['POST'])
def receive_data():
    try:
        data = request.get_json()

        temperature = data.get('temperature')  
        humidity = data.get('humidity') 

        if temperature is None or humidity is None:  
            return jsonify({"error": "Data tidak valid"})

        print(f"Data yang diterima - Suhu: {temperature}, Kelembapan: {humidity}")

        return jsonify({"message": "Data berhasil diterima"})

    except Exception as e:  # Menangani kesalahan jika terjadi
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001)  
