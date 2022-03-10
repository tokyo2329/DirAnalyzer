pipeline {

    agent any

    stages {

        stage("build") {
            steps {
                echo "building the app..."
                sh 'docker build . -t analyzer:latest'
            }
        }

        stage("deploy") {
            steps {
                echo "deploying the app..."
                sh 'docker run analyzer:latest'
                echo ":)"
            }
        }

    }

}